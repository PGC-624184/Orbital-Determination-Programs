#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <read_data.h>

void partials(float *state, int t, float *rho, float *G);
void Radial(float *state, int t, float *rho);

int main(int argc, char *argv[])
{
    char fname[1024];
    FILE *fp;

    if (argc != 2)
    {
        return -1;
    }

    strcpy(fname, argv[1]);
    printf("The file name is %s\n", fname);

    fp = fopen(fname, "r");
    if (fp == NULL)
    {
        printf("Failed to open the file.\n");
        fclose(fp);
        return -1;
    };

    int MAX_ROWS = 5;
    float result[MAX_ROWS][2];

    read_data(fp, result, MAX_ROWS);

    float state[5] = {1.5, 10.0, 2.2, 0.5, 0.3};

    float *rho;
    rho = (float *)malloc(MAX_ROWS * sizeof(float));
    // Calculate rho based on the state
    for (int i = 0; i < MAX_ROWS; i++)
    {
        Radial(state, i, rho);
        printf("Predicted: %f\tActual: %f\n", rho[i], result[i][1]);
    }

    for (int i=0;i<5;i++) {
        printf("%f\n",state[i]);
    }

    // calculate the Jacobian
    float G[5][5];
    for (int i=0;i<MAX_ROWS;i++){
        for (int j=0;j<MAX_ROWS;j++) {
            Radial(state,i,rho);
            partials(state,i,rho,G[i]);
        }
    }

    for (int i=0; i< MAX_ROWS; i++) {
        for (int j=0;j<MAX_ROWS;j++) {
            printf("%f\t",G[i][j]);
        }
        printf("\n");
    }
   
    // These are the correct values from the Textbook for the answer.
    float state2[5] = {1.0, 8.0, 2.0, 1.0, 0.5};

    float *rho2;
    rho2 = (float *)malloc(MAX_ROWS * sizeof(float));

    for (int i = 0; i < MAX_ROWS; i++)
    {
        Radial(state2, i, rho2);
        // printf("%f\n",result[i][1] - rho2[i]);
    }

    free(rho);
    free(rho2);

    return 0;
}

void Radial(float *state, int t, float *rho)
{
    float A_X, A_Y;
    A_X = state[0] - 1.0 + state[2] * (float)t;
    A_Y = state[1] - 1.0 + state[3] * (float)t - 0.5 * state[4] * pow((float)t, 2);
    rho[t] = sqrt(pow(A_X, 2) + pow(A_Y, 2));
}

void partials(float *state, int t, float *rho, float *G)
{
    t = (float)t;
    G[0] = (-1.0 + t * state[2] + state[0]);
    G[1] = (-1.0 - 0.5 * state[4] * pow(t,2) + state[3] * t + state[1]);
    G[2] = (t * (-1.0 + t * state[2] + state[0]));
    G[3] = (t * (-1.0 - 0.5 * state[4] * pow(t,2) + state[3] * t + state[1]));
    G[4] = (-0.5 * pow(t, 2) * state[4]) * (-1.0 - 0.5 * state[4] * pow(t, 2) + state[3] * t + state[1]);
    t = (int)t;
    for (int i = 0; i < 5; i++)
    {
        G[i] = G[i]/rho[t];
    }
}