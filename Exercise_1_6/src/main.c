#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <read_data.h>

void partials(float *state, int t, float *rho, float *G);
void Radial(float *state, int t, float *rho);

int main(int argc, char *argv[]) {
    char fname[1024];
    FILE *fp;
    
    if (argc != 2) {
        return -1;
    }

    strcpy(fname, argv[1]);
    printf("The file name is %s\n", fname);

    fp = fopen(fname, "r");
    if (fp==NULL) {
        printf("Failed to open the file.\n");
        fclose(fp);
        return -1;
    };

    
    int MAX_ROWS = 5;
    float result[MAX_ROWS][2];
    
    read_data(fp, result, MAX_ROWS);

    float state[5] = {1.5, 10.0, 2.2, 0.5, 0.3};
    
    float *rho;
    rho = (float *)malloc(MAX_ROWS*sizeof(float));
    float J[5];
    // Calculate rho based on the state
    for (int i=0; i< MAX_ROWS; i++) {
        Radial(state, i, rho);
        printf("Predicted: %f\tActual: %f\n",rho[i], result[i][1]);
    }
    
    // calculate the difference J
    for (int i=0; i< MAX_ROWS; i++) {
        J[i] = result[i][1] - rho[i];
        printf("The difference between the expected and predicted is: %f\n",J[i]);
    }

    // calculate the partial derivatives at time 0
    float *G;
    int time=0;
    G = (float *)malloc(MAX_ROWS*sizeof(float));

    partials(state,time, rho,G);


    for (int i=0; i< MAX_ROWS; i++) {
            printf("The Partial Derivative is: %f\n",G[i]);
    }

    for (int i=0; i< MAX_ROWS; i++) {
            printf("The state is: %f\n",state[i]);
    }






    // These are the correct values from the Textbook for the answer.
    float state2[5] = {1.0, 8.0, 2.0, 1.0, 0.5};
    
    float *rho2;
    rho2 = (float *)malloc(MAX_ROWS*sizeof(float));

    for (int i=0;i<MAX_ROWS;i++) {
        Radial(state2,i,rho2);
        //printf("%f\n",result[i][1] - rho2[i]);
    }

    free(rho);
    free(rho2);
    free(G);


    return 0;
}

void Radial(float *state, int t, float *rho) {
    float A_X, A_Y; 
    A_X = state[0] - 1.0 + state[2] * (float)t;
    A_Y = state[1] - 1.0 + state[3] * (float)t - 0.5 * state[4] * pow((float)t,2);
    rho[t] = sqrt(pow(A_X,2) + pow(A_Y,2));
}

void partials(float *state, int t, float *rho, float *G) {
    G[0] = (-1.0 + (float)t * state[2]+state[0])/rho[t];
    G[1] = (-1.0 - 0.5*state[4]*(float)t*(float)t + state[3]*(float)t+state[1])/rho[t];
    G[2] = ((float)t * (-1.0 + (float)t * state[2]+state[0]))/rho[t];
    G[3] = ((float)t*(-1.0 -0.5*state[4]*(float)t*(float)t + state[3]*(float)t+state[1]))/rho[t];
    G[4] = ((-0.5*pow((float)t,2)*state[4])*(-1.0 -0.5*state[4]*pow((float)t,2) + state[3]*(float)t+state[1]))/rho[t];
}