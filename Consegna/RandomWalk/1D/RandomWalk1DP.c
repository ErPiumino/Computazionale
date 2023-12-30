#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#define M_PI 3.14159265358979323846264338327950288419716939937510

typedef int iterator;
typedef unsigned long int randn;

struct RandomParameters{
    randn seed;
    randn n; //Number Generated
};

void RW(int argc, char **argv);
int Random(struct RandomParameters *RP);

int main(int argc, char **argv){
    RW(argc, argv);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void RW(int argc, char **argv){
    randn min=1, max=2, x;
    struct RandomParameters RP;
    FILE *fp;
    if(argc !=4){
		printf("\nInput must be: x0(starting point), tmax(total time of integration), Nsim(number of total RW)\n");
		exit(1);
	}
    int nmax = atoi(argv[2]);
    int Nsim = atoi(argv[3]);
    RP.seed = time(NULL);
    char NomeFile[70];
    sprintf(NomeFile, "RW1DPt=%i.dat", nmax);
    fp = fopen(NomeFile, "w+");
    for(int j=0; j<Nsim; j++){
        int r = atoi(argv[1]);
        for(int i=0; i<nmax; i++){
            x = min + (Random(&RP)  % (max - min + 1)); //Get x within range
            if(x==1){ //Going right
                r += 1;}
            if(x==2){ //Going left
                r -= 1;}
        }
        double p = sqrt(1/(M_PI*nmax))*exp(-((double)(r*r)) / (nmax*1*1));
        fprintf(fp, "%i %.5lf\n", r, p);
    }
    fclose(fp);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
int Random(struct RandomParameters *RP){
    randn a=pow(5,5), c=pow(7,5), m=1944674407370955169; //a:constant multiplier, c:increment, m:modulus

	RP->n =(a*(RP->seed) + c) % m; //Generate random
    RP->seed = RP->n; //Update seed
    return RP->n;
}