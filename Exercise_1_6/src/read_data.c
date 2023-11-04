#include <stdio.h>
#include <read_data.h>

void read_data(FILE *fp, float (*result)[2], int maxRows) {
    float time, rho;
    int i;
    char buf[1024];

    if (fp==NULL) {
        perror("Error opening file. Aborting");
        return;
    }

    for (i=0;i<maxRows;i++) {
        (void)*fgets(buf, sizeof buf, fp);
        sscanf(buf, "%g %g", &time, &rho);
        result[i][0] = time;
        result[i][1] = rho;
    }
    fclose(fp);
}