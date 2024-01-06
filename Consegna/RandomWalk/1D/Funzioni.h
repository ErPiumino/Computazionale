#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>

typedef unsigned long int randn;

typedef struct{
    randn seed;
    randn n; //Number Generated
}RandomParameters;

double Random(RandomParameters *RP);

double** RW(int argv, char *argc[], FILE* gnu){
    FILE* fp;
    char NomeFile[60];
    RandomParameters RP;
    int n = atoi(argc[2]), Nsim = atoi(argc[3]);
    RP.seed = time(NULL);

    double **avg=(double**)calloc(2, sizeof(double*)); 
    for(int i=0; i<2; i++) {
        avg[i] = (double *) calloc(n, sizeof(double));
    }// Saving both average and error in one 2xN matrix
    sprintf(NomeFile, "RW1DHiston=%i.dat", n);
    fp = fopen(NomeFile, "w+");

    for(int j=0; j<Nsim; j++){ //many RWs for histogram, saving all positions for first RW and then just last ones
        int r = atoi(argc[1]); //Initial position
        if(j==0){
        fprintf(gnu, "%i \t %i\n", j+1, r);} //I only graph the trajectory of the first RW
        for(int i=0; i<n; i++){
            double x = Random(&RP);
            x<0.5 ? r++ : r--;
            if(j==0){
            fprintf(gnu, "%i \t %i\n", i+1, r);}
            avg[0][i] += r*r;
            avg[1][i] += r*r*r*r;
        }
        fprintf(fp, "%i\n", r); //Saving the last position of each RW
    }
    fclose(fp);
    return avg;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double Random(RandomParameters *RP){
    randn a=pow(5,5), c=pow(7,5), m=1944674407370955169; //a:constant multiplier, c:increment, m:modulus

	RP->n =(a*(RP->seed) + c) % m; //Generate random
    RP->seed = RP->n; //Update seed
    return (double)RP->n / m;
}