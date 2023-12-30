#include "Funzioni.h"

int main(int argc, char **argv){
    FILE *fp;
    srand(time(NULL));
    if(argc!=5){
        printf("\nInput must be: dro(Delta of ro, in [0,1]), L, tmax(tmax for each simulation), Nsim(total number of simulation for each configuration)\n");
        exit(1);
    }
    double dro = fabs(atof(argv[1]));
    int L = atoi(argv[2]);
    int m = atoi(argv[3]);
    int Nsim = atoi(argv[4]);
    double *D;
    if(dro<0 || dro>1){immission_error();}
    int **reticolo = matrix(L);
    Pos *particelle, *distanzaparticelle;
    for(double ro=dro; ro<1; ro+=dro){
        char NomeFile[80];
        sprintf(NomeFile, "A(t)ro=%.2lfL=%.i.dat", ro, L);
        fp = fopen(NomeFile, "w+");
        if (fp == NULL) {
            printf("\nError opening file, exiting...\n");
            exit(1);
        }
        int N = ro*L*L;
        particelle = array(N, sizeof(Pos));
        distanzaparticelle = array(N, sizeof(Pos));
        D = Density(reticolo, particelle, distanzaparticelle, m, L, N, Nsim, L);
        for(int k=0; k<m; k++){
            fprintf(fp, "%i \t %.5lf\n", k, D[k]);
        }
        free(particelle);
        free(distanzaparticelle);
        free(D);
        fclose(fp);
    }
    for(int j=0; j<L; j++){
        free(reticolo[j]);
    }
    free(reticolo);
}