#include "Funzioni.h"

int main(int argc, char **argv){
    FILE *fp;
    srand(time(NULL));
    if(argc!=6){
        printf("\nInput must be: ro, dL, Lmax, tmax, Nsim\n");
        printf("Note that ro in [0;1]\n");
        exit(1);
    }
    double ro = fabs(atof(argv[1]));
    int dL = atoi(argv[2]);
    int Lmax = atoi(argv[3]);
    int m = atoi(argv[4]);
    int Nsim = atoi(argv[5]);
    double *D;
    if(ro<0 || ro>1){immission_error();}
    Pos* particelle, *distanzaparticelle;
    for(int L=dL; L<=Lmax; L+=dL){
        int **reticolo = matrix(L);
        char NomeFile[80];
        sprintf(NomeFile, "A(t)L=%iro=%.2lf.dat", L, ro);
        fp = fopen(NomeFile, "w+");
        if (fp == NULL) {
            printf("\nError opening file, exiting...\n");
            exit(1);
        }
        int N = ro*L*L;
        particelle = array(N, sizeof(Pos));
        distanzaparticelle = array(N, sizeof(Pos));
        D = Density(reticolo, particelle, distanzaparticelle, m, L, N, Nsim, Lmax);
        for(int k=0; k<m; k++){
            fprintf(fp, "%i \t %.5lf\n", k, D[k]);
        }
        fclose(fp);
        free(particelle);
        free(distanzaparticelle);
        free(D);
        for(int j=0; j<L; j++){
            free(reticolo[j]);
        }
        free(reticolo);
    }
}