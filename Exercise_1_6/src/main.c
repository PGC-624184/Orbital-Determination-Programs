#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <read_data.h>


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
    
    float rho[5];
    //float rhoDot[5];
    float A_X, A_Y;
    
    for (int i=0; i<MAX_ROWS;i++) {
        A_X = state[0] - 1.0 + state[2] * (float)i;
        A_Y = state[1] - 1.0 + state[3] * (float)i - 0.5 * state[4] * (float)i *  (float)i;
        rho[i] = sqrt(A_X*A_X + A_Y*A_Y);
        //rhoDot[i] = 1/rho[i]*(A_X*state[2]+A_Y*state[3]);
        printf("Predicted:\t %g \t Actual: %g\n",rho[i],result[i][1]);
    }

    return 0;
}