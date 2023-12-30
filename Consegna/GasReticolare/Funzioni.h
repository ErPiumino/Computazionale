#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<string.h>

typedef struct Position{
    int x;
    int y;
}Pos;

double INVRANDMAX=1/(RAND_MAX + 1.);
void particleposition(int** matrix, Pos* array, Pos* distanzaparticelle, int L, int N);
int Check(int** reticolo, int x, int y, int L);
double mod(double x, double m);
double R2(Pos *distanzaparticelle, int N);
void ClearReticolo(int** reticolo, int L);
void ClearArray(Pos* particelle, int N);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
double randrange(double a, double b){
    //Generate a random double number in [a,b)
    return rand()*INVRANDMAX*(b-a)+a;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* array(int N, int size){
    //Like calloc, but raises an error if fails to allocate
    void* array = calloc(N, size);
    if (array == NULL){
        fprintf(stderr, "Memory Error: allocation failed\n");
        exit(2);
    }
    return array;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int** matrix(int L){
    //Allocate a matrix of int
    int **matrix = array(L, sizeof(int *));
    for (int i=0; i<L; i++){
        matrix[i] = array(L, sizeof(int));
    }
    return matrix;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void immission_error(){
    printf("\nError in the variable input, try again...\n");
    exit(1);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void spawn(int** reticolo, Pos *array, Pos* distanzaparticelle, int L, int N){
    int n=1;
    while(n<=N){
        int x = randrange(0, L);
        int y = randrange(0, L);
        if(reticolo[x][y]==0){
            reticolo[x][y] = n++;
        }
    }
    particleposition(reticolo, array, distanzaparticelle, L, N);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printmatrix(int** reticolo, int L){
    for(int i=0; i<L; i++){
        for(int j=0; j<L; j++){
            printf("%i\t", reticolo[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printarray(Pos *array, int N){
    //Print nicely the array of positions for debug purposes
    for (int i=0; i<N; i++){
        printf("%i: \t%ix %iy", i+1, array[i].x, array[i].y);
        printf("\n");
    }
    printf("\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void move(int** reticolo, Pos* array, Pos* distanzaparticelle, int N, int L){
    Pos delta, newpos;
    for(int i=0; i<N; i++){
        //Initializing the variables as a safety check
        delta.x = 0; delta.y = 0; newpos.x = 0; newpos.y = 0;
        int r = (rand()%4) + 1; //Generate number within [1;4]
        switch (r){
        case (1):
            delta.x = 1;
            delta.y = 0;
            break;
        case (2):
            delta.x = -1;
            delta.y = 0;
            break;
        case (3):
            delta.x = 0;
            delta.y = 1;
            break;
        case (4):
            delta.x = 0;
            delta.y = -1;
            break;
        }
        newpos.y = mod(array[i].y+delta.y, L);
        newpos.x = mod(array[i].x+delta.x, L);
        if(Check(reticolo, newpos.x, newpos.y, L)==1){
            reticolo[array[i].y][array[i].x] = 0; //Freeing the spot early occupied by the particle
            array[i].x = newpos.x; //Updating positions
            array[i].y = newpos.y;
            reticolo[newpos.y][newpos.x] = i+1; //Occuping the actual spot of the particle
            distanzaparticelle[i].x += delta.x;
            distanzaparticelle[i].y += delta.y;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void particleposition(int** matrix, Pos* array, Pos* distanzaparticelle, int L, int N){
    //Sync the array of positions with the matrix
    for (int i=0; i<L; i++){
        for(int j=0; j<L; j++){
            int p = matrix[i][j];
            if (p != 0){
                array[p-1].x = j;
                array[p-1].y = i;
                distanzaparticelle[p-1].x = 0;
                distanzaparticelle[p-1].y = 0;
            }
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Check(int** reticolo, int x, int y, int L){
    if(x<0 || x>L-1 || y<0 || y>L-1){
        return 0; //To exlcude segmentation fault, not a problem since the mod function will take care of it
    }
    if(reticolo[y][x]==0){
        return 1;
    }
    else{
        return 0;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
double* Density(int** reticolo, Pos* particelle, Pos* distanzaparticelle, int m, int L, int N, int Nsim, int Lmax){
    double *avg = array(m, sizeof(double));
    memset(avg, 0, m * sizeof(double));
    for(int i=0; i<Nsim; i++){
        ClearReticolo(reticolo, L);
        ClearArray(distanzaparticelle, N);
        ClearArray(particelle, N);
        spawn(reticolo, particelle, distanzaparticelle, L, N);
        for(int j=0; j<m; j++){
            move(reticolo, particelle, distanzaparticelle, N, L);
            avg[j] += R2(distanzaparticelle, N);
            //printf("%.2lf \t", avg[j]);
        }
    }
    for(int i=0; i<m; i++){
        avg[i] = avg[i]/(Nsim*4*(i));
    }
    return avg;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
double R2(Pos *distanzaparticelle, int N){
    //Calculate the average R^2 where R is the distance from the starting
    //Point of every particle.
    double res = 0;
    for (int i=0; i<N; i++){
        res += distanzaparticelle[i].x*distanzaparticelle[i].x + distanzaparticelle[i].y*distanzaparticelle[i].y;
    }
    return res/N;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
double mod(double x, double m){
    //Compute x mod. m. Result is in [0,m)
    return fmod(fmod(x, m) + m, m);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClearReticolo(int** reticolo, int L){
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            reticolo[i][j] = 0;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClearArray(Pos* particelle, int N){
    for(int i=0; i<N; i++){
        particelle[i].x = 0;
        particelle[i].y = 0;
    }
}