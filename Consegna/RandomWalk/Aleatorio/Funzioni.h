#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<string.h>

typedef unsigned long int randn;

typedef struct{
    randn seed;
    randn n;//Number Generated
}RandomParameters;

double Random(RandomParameters *RP);

double* RW(int argv, char *argc[], FILE* gnu){
    RandomParameters RP;
    RP.seed = time(NULL);
    int n = atoi(argc[1]);
    int Nsim = atoi(argc[2]);

    double *mean=(double*)calloc(2*n+1, sizeof(double*)); 

    for(int s=0; s<Nsim; s++){
        int r = 0;
        double *Percorso=(double*)calloc(2*n+1, sizeof(double*));
        for(int i=0; i<2*n+1; i++){
            Percorso[i] = Random(&RP);
        }

        for(int i=0; i<n; i++){
            if(s==0){
                fprintf(gnu, "%i %i\n", i+1, r);
            }
            double d = Random(&RP);
            d<Percorso[r+Nsim] ? r++ : r--;
            mean[i] += (double) r*r;
        }
        free(Percorso);
    }

    return mean;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double Random(RandomParameters *RP){
    randn a=pow(5,5), c=pow(7,5), m=1944674407370955169; //a:constant multiplier, c:increment, m:modulus

	RP->n =(a*(RP->seed) + c) % m; //Generate random
    RP->seed = RP->n; //Update seed
    return ((double)RP->n / m); //Convert RP->n to a value between 0 and 1
}