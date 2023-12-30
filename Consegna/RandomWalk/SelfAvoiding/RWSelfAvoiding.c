//2D self avoiding random walk
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
int Check(int **walk, int x, int y, int step);
int Random(struct RandomParameters *RP);
int Trapped(int **walk, int step);
void Python(int trapped[6]);

int main(int argc, char **argv){
    RW(argc, argv);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void RW(int argc, char **argv){
    randn p;
    struct RandomParameters RP;
    iterator nmax;
    FILE *fp;
    if(argc !=4){
		printf("\nInput must be: x0(starting point), y0(starting point), nmax(total number of steps)\n");
		exit(1);
	}
    RP.seed = time(NULL);
    nmax = atoi(argv[3]);
    for(int k=0; k<6; k++){
        //////////////////Creating 2dimensional array using calloc//////////////////
        int **position=(int**)calloc(nmax, sizeof(int*)); 
        for(int i=0; i<nmax; i++) {
            position[i] = (int *) calloc(2, sizeof(int));
        }
        ////////////////////////////////////////////////////////////////////////////
        int n=1;
        position[0][0] = atoi(argv[1]);
        position[0][1] = atoi(argv[2]);
        char NomeFile[70];
        sprintf(NomeFile, "SelfAvoidingn=%i.dat", nmax-2);
        fp = fopen(NomeFile, "w+");
        while(n<nmax){
            //Check if the starting position of every cycle is trapped
            if(Trapped(position, n-1)==1){
                    printf("Trapped at %i \t\t %i \t\t %i\n", position[n-1][0], position[n-1][1], n-1);
                    fprintf(fp, "%i \t\t %i \t\t %i\n", position[n-1][0], position[n-1][1], n-1);
                    break;
            }
            p = (Random(&RP) % 4 + 4) % 4 + 1; //x will be in the range [1, 4]
            int dx=0, dy=0;
            // Move in the chosen direction
            switch (p) {
                case 1: // Up
                    dy = -1;
                    break;
                case 2: // Down
                    dy = 1;
                    break;
                case 3: // Left
                    dx = -1;
                    break;
                case 4: // Right
                    dx = 1;
                    break;
            }
            // Check if the new position has already been visited
            if(Check(position, position[n-1][0]+dx, position[n-1][1]+dy, n) == 0){
                position[n][0] = position[n-1][0] + dx;
                position[n][1] = position[n-1][1] + dy;
                fprintf(fp, "%i \t\t %i \t\t %i\n", position[n-1][0], position[n-1][1], n-1);
                n++;
            }
        }
        fclose(fp);
        //Free the allocated memory
        for (int i=0; i<nmax; i++) {
            free(position[i]);
        }
        free(position);
        nmax = (nmax-2)*5 +2;
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
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
int Check(int **walk, int x, int y, int step) {
    int controllo = 0;
    for (int i=0; i<step; i++){
        if (walk[i][0] == x && walk[i][1] == y) {
            controllo = 1;
        }
    }
    return controllo;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
int Trapped(int **walk, int step){
    // Check all possible moves
    if(
    Check(walk, walk[step][0]+1, walk[step][1]+0, step) == 1  &&  
    Check(walk, walk[step][0]-1, walk[step][1]+0, step) == 1  &&  
    Check(walk, walk[step][0]+0, walk[step][1]+1, step) == 1  && 
    Check(walk, walk[step][0]+0, walk[step][1]-1, step) == 1) {
        return 1;
    }
    else{
        return 0;
    }
}