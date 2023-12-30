#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

int n;

typedef unsigned long int randn;

struct RandomParameters{
    randn seed;
    randn n; //Number Generated
};
struct Position{
    int x;
    int y;
};
struct Probability{
    double x;
    double y;
};

void RW(int argc, char **argv);
int Random(struct RandomParameters *RP);

int main(int argc, char **argv){
    RW(argc, argv);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void RW(int argc, char **argv){
    randn min=1, max=4, x;
    struct RandomParameters RP;
    struct Position r;
    struct Probability p;
    if(argc !=5){
		printf("\nInput must be: x0(starting point), y0(starting point), n(number of steps), k(number of total random walks)\n");
		exit(1);
	}
    int n = atoi(argv[3]);
    int ktot = atoi(argv[4]);
    RP.seed = time(NULL);
    r.x = atoi(argv[1]); //Initial position
    r.y = atoi(argv[2]); //Initial position
    char NomeFile1[70], NomeFile2[70];
    sprintf(NomeFile1, "RW2DHiston=%i.dat", n);
    sprintf(NomeFile2, "RW2DPt=%i.dat", n);
    FILE *fp1 = fopen(NomeFile1, "w+");
    FILE *fp2 = fopen(NomeFile2, "w+");
    for(int k=0; k<ktot; k++){ //Doing ktot different random walks 
        r.x = atoi(argv[1]); //Initial position
        r.y = atoi(argv[2]); //Initial position
        for(int i=0; i<n; i++){ //Main cycle 
            x = Random(&RP);
            x = min + (x % (max - min + 1)); //Get x within range
            if(x==1){ //Going up, following clockwise 1,2,3,4
                r.y += 1;}
            if(x==2){ //Going right, following clockwise 1,2,3,4
                r.x += 1;}
            if(x==3){ //Going down, following clockwise 1,2,3,4
                r.y -= 1;}
            if(x==4){ //Going left, following clockwise 1,2,3,4
                r.x -= 1;}
        }
        p.x = sqrt(1/(M_PI*n))*exp(-((double)(r.x*r.x)) / (n*1*1));
        p.y = sqrt(1/(M_PI*n))*exp(-((double)(r.y*r.y)) / (n*1*1));
        double prob = p.x * p.y;
        fprintf(fp1, "%i \t %i\n", r.x, r.y); //Fprinting the final position of each RW
        fprintf(fp2, "%i \t %i \t %lf\n", r.x, r.y, prob); 
    }
    fclose(fp1);
    fclose(fp2);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
int Random(struct RandomParameters *RP){
    randn a=pow(5,5), c=pow(7,5), m=1944674407370955169; //a:constant multiplier, c:increment, m:modulus

	RP->n =(a*(RP->seed) + c) % m; //Generate random
    RP->seed = RP->n; //Update seed
    return RP->n;
}