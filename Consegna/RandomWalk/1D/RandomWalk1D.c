#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

int n;

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
    double mean, mean2, std;
    randn min=1, max=2, x;
    struct RandomParameters RP;
    int r; //r equal position
    iterator i=0, k, j, jtot;
    FILE *fp, *fp1, *fp2;
    if(argc !=4){
		printf("\nInput must be: x0(starting point), n(number of steps), k(number of total RW for histogram)\n");
		exit(1);
	}
    n = atoi(argv[2]);
    jtot = atoi(argv[3]);
    RP.seed = time(NULL);
    for(k=0; k<6; k++){ //based on n
        i=0;
        char NomeFile[60];
        char NomeFile1[60];
        char NomeFile2[60];
        sprintf(NomeFile, "RW1Dn=%i.dat", n);
        sprintf(NomeFile1, "1DMuStdn=%i.dat", n);
        sprintf(NomeFile2, "RW1DHiston=%i.dat", n);
        fp = fopen(NomeFile, "w+");
        fp1 = fopen(NomeFile1, "w+");
        fp2 = fopen(NomeFile2, "w+");
        for(j=0; j<jtot; j++){ //many RWs for histogram, saving all positions for first RW and then just last ones
            r = atoi(argv[1]); //Initial position
            if(j==0){
            fprintf(fp, "%i \t %i\n", r, i);}
            for(i=0; i<n; i++){
                x = Random(&RP);
                x = min + (x % (max - min + 1)); //Get x within range
                if(x==1){ //Going right
                    r += 1;}
                if(x==2){ //Going left
                    r -= 1;}
                if(j==0){
                fprintf(fp, "%i \t %i\n", r, i+1);}
            }
            fprintf(fp2, "%i\n", r); //Saving the last position of each RW
            if(j==0){
                mean = fabs((double)r/n);
                mean2 = fabs((double)pow(r,2)/n);
                std = sqrt(mean2 - pow(mean, 2));
                fprintf(fp1, "%.2lf \t %.2lf\n", mean, std);
            }
        }
        fclose(fp);
        fclose(fp1);
        fclose(fp2);
        n+=5*n;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
int Random(struct RandomParameters *RP){
    randn a=pow(5,5), c=pow(7,5), m=1944674407370955169; //a:constant multiplier, c:increment, m:modulus

	RP->n =(a*(RP->seed) + c) % m; //Generate random
    RP->seed = RP->n; //Update seed
    return RP->n;
}