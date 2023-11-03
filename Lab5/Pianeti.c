#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define G 0.0000000000677

struct Position{
    double x;
    double y;
    double z;
};
struct Velocity{
    double x;
    double y;
    double z;
};
struct K{
    double k1;
    double k2;
    double k3;
}

typedef int iterator;

void Algoritmo(int argc, char **argv);
void Passo(struct Position *r, struct Velocity *v, struct K k1, struct K k2, struct K k3, struct K k4, double dt, double tmax, int i);
struct K Force(struct K k, double x0, double v0, double dt, double t);

int main(int argc, char **argv){
    Algoritmo(int argc, char **argv);
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void Algoritmo(int argc, char **argv){
    struct Position r1, r2;
    struct Velocity v1, v2;
    struct K k1, k2, k3, k4;
}