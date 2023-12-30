//1D Random Walk with different probability for each pass
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

int n;

typedef unsigned long int randn;

struct RandomParameters{
    randn seed;
    randn n;//Number Generated
};
struct Probability{
    double p;
    double q;//q=1-p
};

void RW(int argc, char **argv);
int Random(struct RandomParameters *RP, struct Probability *P);

int main(int argc, char **argv){
    RW(argc, argv);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void RW(int argc, char **argv){
    randn x;
    struct RandomParameters RP;
    struct Probability P;
    int r; //r equal position
    FILE *fp, *fp1;
    if(argc !=4 || atof(argv[3])<0 || atof(argv[3])>1){
		printf("\nInput must be: x0(starting point), n(number of initial steps), p(probability of going right on first step, where p in [0;1])\n");
		exit(1);
	}
    n = atoi(argv[2]);
    P.p = atof(argv[3]);
    P.q = 1-P.p;
    RP.seed = time(NULL);
    for(int k=0; k<6; k++){ //based on n, increasing each time
        r = atoi(argv[1]); //Initial position, has to be initialized
        char NomeFile[60];
        sprintf(NomeFile, "RWTrapn=%ip=%.2lf.dat", n, P.p);
        fp = fopen(NomeFile, "w+");
        fprintf(fp, "%i \t %i\n", r, 0);
        for(int i=0; i<n; i++){
            x = Random(&RP, &P);
            switch (x){
            case 1:
                r ++; //Going right
                break;
            case 2:
                r --; //Going left
                break;
            }
            fprintf(fp, "%i \t %i\n", r, i+1);
        }
        fclose(fp);
        n += 5*n;
    }
    Python(P.p, atof(argv[2]));
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
int Random(struct RandomParameters *RP, struct Probability *P){
    randn a=pow(5,5), c=pow(7,5), m=1944674407370955169, x; //a:constant multiplier, c:increment, m:modulus

	RP->n =(a*(RP->seed) + c) % m; //Generate random
    RP->seed = RP->n; //Update seed
    double randomValue = (double)RP->n / m; //Convert RP->n to a value between 0 and 1
    if (randomValue < P->p) {//Check if the random number falls within the desired probability
        x = 1; //Probability of going right
    } else {
        x = 2; //Probability of going left, 1-p
    }
    double temp = P->p;
    P->p = P->q;
    P->q = temp;
    return x;
}