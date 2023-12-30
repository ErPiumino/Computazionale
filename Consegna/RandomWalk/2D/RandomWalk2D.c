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
struct Position{
    int x;
    int y;
};
struct Mean{
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
    randn min=1, max=4, x, z;
    struct RandomParameters RP;
    struct Position r, sum;
    struct Mean mean, meanx2, std;
    iterator i, k;
    int nx=0, ny=0;
    FILE *fp, *fp1;
    if(argc !=4){
		printf("\nInput must be: x0(starting point), y0(starting point), n(number of steps)\n");
		exit(1);
	}
    n = atoi(argv[3]);
    RP.seed = time(NULL);
    for(k=0; k<6; k++){
        z=0;
        r.x = atoi(argv[1]); //Initial position
        r.y = atoi(argv[2]); //Initial position
        sum.x = 0;
        sum.y = 0;
        char NomeFile[60];
        char NomeFile1[60];
        sprintf(NomeFile, "RW2Dn=%i.dat", n);
        sprintf(NomeFile1, "MuStdn=%i.dat", n);
        fp = fopen(NomeFile, "w+");
        fp1 = fopen(NomeFile1, "w+");
        fprintf(fp, "%i \t %i\n", r.x, r.y);
        for(i=0; i<n; i++){
            x = Random(&RP);
            x = min + (x % (max - min + 1)); //Get x within range
            z += x;
            if(x==1){ //Going up, following clockwise 1,2,3,4
                r.y += 1;
                sum.y += 1;
                ny++;}
            if(x==2){ //Going right, following clockwise 1,2,3,4
                r.x += 1;
                sum.x += 1;
                nx++;}
            if(x==3){ //Going down, following clockwise 1,2,3,4
                r.y -= 1;
                sum.y += 1;
                ny++;}
            if(x==4){ //Going left, following clockwise 1,2,3,4
                r.x -= 1;
                sum.x += 1;
                nx++;}
            fprintf(fp, "%i \t %i\n", r.x, r.y);
        }
        fclose(fp);
        mean.x = fabs((double)r.x/nx);
        mean.y = fabs((double)r.y/ny);
        meanx2.x = fabs((double)pow(r.x,2)/nx);
        meanx2.y = fabs((double)pow(r.y,2)/ny);
        std.x = sqrt(meanx2.x - pow(mean.x, 2));
        std.y = sqrt(meanx2.y - pow(mean.y, 2));
        fprintf(fp1, "%.2lf \t %.2lf \t %.2lf \t %.2lf\n", mean.x, mean.y, std.x, std.y);
        printf("\nMedie(x,y): \t (%.2lf +- %.2lf, %.2lf +- %.2lf) \t (n=%i) \nMedia Numeri randomici: \t %.2lf\n\n", mean.x, std.x, mean.y, std.y, n, (double)z/n);
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