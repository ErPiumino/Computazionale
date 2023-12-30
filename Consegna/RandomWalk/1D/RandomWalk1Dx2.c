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

void RW(int argc, char **argv);
int Random(struct RandomParameters *RP);

int main(int argc, char **argv){
    RW(argc, argv);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void RW(int argc, char **argv){
    int r;
    randn min=1, max=2, x;
    struct RandomParameters RP;
    iterator nmax, dn, iterations;
    FILE *fp;
    if(argc !=4){
		printf("\nInput must be: x0(starting point), tmax(total time of integration), k(number of total RW for x(t)^2, must be a multiple)\n");
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
    fp = fopen("<x2>.dat", "w+");
    for(int j=0; j<=nmax; j++){
        r = atoi(argv[1]);
        for(int i=0; i<nmax; i++){
            x = Random(&RP);
            x = min + (x % (max - min + 1)); //Get x within range
            if(x==1){ //Going right
                r += 1;}
            if(x==2){ //Going left
                r -= 1;}
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
int Random(struct RandomParameters *RP){
    randn a=pow(5,5), c=pow(7,5), m=1944674407370955169; //a:constant multiplier, c:increment, m:modulus

	RP->n =(a*(RP->seed) + c) % m; //Generate random
    RP->seed = RP->n; //Update seed
    return RP->n;
}