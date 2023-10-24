#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct coord
{
    double x;
    double v;
};

struct input{
    double x0;
    double v0;
    double omega2;
    double dt;
    double T;
    double fext;
    double beta;
};


struct coord prodotto(struct coord a ,double b);
struct coord somma(struct coord a,struct coord b);
struct coord iniziali(double x0,double v0);
struct coord derivata(struct coord* XandV,double omega2);
void RungeKutta4(FILE*fp,struct coord *xv,struct input *IC,double *t,double freq);

int main(int argc,char **argv) {
    int n;
    FILE* fp;
    double x0,v0,T,dt,omega2,beta,fext,t,freq=2./3.;
    struct input iniziali;
    struct coord coordinate;
    struct input  *IC;
    struct coord *P;
    P=&coordinate;
    IC=&iniziali;
    if(argc != 8){
        printf("L'input deve essere x0 v0 T dt omega2 beta f\n");
        return 1;
    }
    IC->x0=strtod(argv[1],NULL);
    IC->v0=strtod(argv[2],NULL);
    IC->T=strtod(argv[3],NULL);
    IC->dt=strtod(argv[4],NULL);
    IC->omega2=strtod(argv[5],NULL);
    IC->beta=strtod(argv[6],NULL);
    IC->fext=strtod(argv[7],NULL);
    P->x=IC->x0;
    P->v=IC->v0;
    n=(int)IC->T/IC->dt;
    fp=fopen("Rk4_new.dat","w");
    for(int i=0;i<n;i++){
    RungeKutta4(fp,P,IC,&t,freq);
    }
    fclose(fp);
}
  


struct coord derivate(struct coord* xv, struct input* IC, double t,double freq){ //Calcolo del tasso di cambiamento
    struct coord D;
    D.x=xv->v;
    D.v=-(IC->omega2*sin(xv->x))-((IC->beta)*xv->v)+(IC->fext)*cos(freq*t);
    return D;
}

struct coord somma(struct coord a,struct coord b){
    struct coord S;
    S.x=a.x+b.x;
    S.v=a.v+b.v;
    return S;
};

struct coord prodotto(struct coord a ,double b){
   struct  coord P;
   P.x=a.x*b;
   P.v=a.v*b;
   return P;
};

void RungeKutta4(FILE*fp,struct coord *xv,struct input *IC,double *t,double freq){
    struct coord D,K1,K2,K3,K4;
    struct coord xvs;
    D = derivate(xv,IC,*t,freq);
    K1=prodotto(D,IC->dt);
    xvs=somma(*xv,prodotto(K1,0.5));
    D= derivate(&xvs,IC,*t+0.5*IC->dt,freq);
    K2=prodotto(D,IC->dt);
    xvs=somma(*xv,prodotto(K2,0.5));
    D= derivate(&xvs,IC,*t+0.5*IC->dt,freq);
    K3=prodotto(D,IC->dt);
    xvs=somma(*xv,K3);
    D= derivate(&xvs,IC,*t+IC->dt,freq);
    K4=prodotto(D,IC->dt);
    *xv=somma(*xv,prodotto((somma((somma((somma(K1,prodotto(K2,2))),prodotto(K3,2))),K4)),((double)1/6)));
    *t+=IC->dt;
    fprintf(fp,"%lf %lf %lf\n",*t,xv->x,xv->v);
};









