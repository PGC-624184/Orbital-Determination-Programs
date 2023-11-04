#include <math.h>
#include <stdio.h>
#include <newton_raphson.h>

void newton_raphson(float *state, float *rho, int n) {
    float A_X, A_Y;

    if ((state == NULL) || (rho == NULL)) {
        perror("Error opening vectors. Aborting");
        return;
    }
    
    for (int i=0; i<n;i++) {
        A_X = state[0] - 1.0 + state[2] * (float)i;
        A_Y = state[1] - 1.0 + state[3] * (float)i - 0.5 * state[4] * (float)i *  (float)i;
        rho[i] = (float)sqrt(A_X*A_X + A_Y*A_Y);
        printf("The state rho: %g", rho[i]);
    }
    
}