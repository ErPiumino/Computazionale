#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

typedef int iterator;
typedef unsigned long int randn;

struct RandomParameters{
    randn seed;
    randn n; //Number Generated
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
    iterator nmax, iterations;
    FILE *fp;
    if(argc !=5){
		printf("\nInput must be: x0(starting point), nmax(max number of steps), k(number of iterations, multiple of nmax), p(probability of going right, where p in [0;1])\n");
		exit(1);
	}
    nmax = atoi(argv[2]);
    iterations = atoi(argv[3]);
    int *av=(int*)calloc(nmax, sizeof(int)); //To store average position
    int *av1=(int*)calloc(nmax, sizeof(int)); 
    if((nmax%iterations)!=0 || nmax<iterations){
        printf("\nError, number of iterations must be an int, not a float...\n");
        exit(1);
    }
    RP.seed = time(NULL);
    fp = fopen("/workspaces/Computazionale2/RandomWalk/File/RWTrapx2.dat", "w+");
    for(int j=0; j<=nmax; j++){
        r = atoi(argv[1]);
        P.p = atof(argv[4]);
        P.q = 1-P.p;
        for(int i=0; i<nmax; i++){
            x = Random(&RP, &P);
            switch (x){
            case 1:
                r ++; //Going right
                break;
            case 2:
                r --; //Going left
                break;
            }
            av[i] += r*r;
            av1[i] += r*r*r*r;
        }
    }
    for(int i=0; i<nmax; i++){
        fprintf(fp, "%.2lf \t %.2lf \t %i\n", av[i]/(double)nmax, av1[i]/(double)(nmax), i);
    }
    fclose(fp);
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