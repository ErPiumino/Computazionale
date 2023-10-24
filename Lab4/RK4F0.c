//Runge-Kutta 4 using structs. Actual Physics problem: caotic Pendulum with study of f0 variation
//Parametri per studio di forzante conformi a quelli su E-learning: 1.570796327 0 1 0.5 2/3. 0.9 100 0.001 1
//x(0)=pi/2 circa 1.570796327
//v(0)=0
//omega2=1
//gamma=0.5
//omegaext=2/3.
//f0=0.9
//tmax=100
//dt=0.001
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef int iterator;

struct Phase{
    double x;
    double v;
};
struct K{
	double k1;
	double k2;
};

void Algoritmo(int argc, char **argv);
void Passo(struct Phase *xv, struct K *k1, struct K *k2, struct K *k3, struct K *k4, double omega2, double omegaext, double f0, double gamma, double dt, double tmax, int i);
struct K Force(struct K k, double x0, double v0, double dt, double omega2, double gamma, double f0, double omegaext, double t);
double Energy(struct Phase xv, double omega2);

int main(int argc, char **argv){
	Algoritmo(argc, argv); 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algoritmo (int argc, char **argv){
    struct Phase xv;
    struct K k1, k2, k3, k4;
	double omega2, omegaext, gamma, f0, tmax, dt, E0, E, Emax, x0, v0;
	iterator k, i;
	int n, ciclo=1;
	FILE *fp;
	if(argc !=9){
		printf("\nInput must be: theta0(deg) dtheta0/dt(rad/s) omega2(rad/s^2) gamma omegaext f0 tmax(s) dt(s)\n");
		exit(1);
	}
	//Lettura variabili e apertura file
	xv.x = atof(argv[1]);//atof legge un float, atoi per gli int
	xv.v = atof(argv[2]);
	omega2 = atof(argv[3]);
	gamma = atof(argv[4]);
	omegaext = atof(argv[5]);
	f0 = atof(argv[6]);
	tmax = atof(argv[7]);
	dt = atof(argv[8]);
	n=tmax/dt;
	E0=Energy(xv, omega2);
	char NomeFile[50];
	sprintf(NomeFile, "PendoloCaoticoF0%.3lf.dat", f0); //Salvo i dati delle varie forzanti in file diversi
	fp = fopen(NomeFile, "w");
	fprintf(fp, "\t %.20lf \t %.20lf \t 0.00 \t %e \n", xv.x, xv.v, E0);
	//Passi algoritmo
	for(i=1; i<=n; i++){
		x0=xv.x;
		v0=xv.v;
		k1 = Force(k1, x0, v0, dt, omega2, gamma, f0, omegaext, i*dt);
		k2 = Force(k2, x0+k1.k1/2., v0+k1.k2/2., dt, omega2, gamma, f0, omegaext, i*dt+dt/2.);
		k3 = Force(k3, x0+k2.k1/2., v0+k2.k2/2., dt, omega2, gamma, f0, omegaext, i*dt+dt/2.);
		k4 = Force(k4, x0+k3.k1, v0+k3.k2, dt, omega2, gamma, f0, omegaext, i*dt+dt);
		Passo(&xv, &k1, &k2, &k3, &k4, omega2, omegaext, f0, gamma, dt, tmax, i);
		E=Energy(xv, omega2);
		fprintf(fp,"\t %.20lf \t %.20lf \t %.20lf \t %e\n", xv.x, xv.v, (double)i*dt, E);
		if(Emax<E){
			Emax=E; //Segno l'"Errore massimo" commesso in base al dt, altrimenti l'errore relativo sarebbe falsato
		}
	}
	//Inizializzo le variabili
	xv.x = atof(argv[1]);
	xv.v = atof(argv[2]);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double Energy(struct Phase xv, double omega2){
    return (xv.v*xv.v + omega2*(1.-cos(xv.x)));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Passo (struct Phase *xv, struct K *k1, struct K *k2, struct K *k3, struct K *k4, double omega2, double omegaext, double f0, double gamma, double dt, double tmax, int i){
    double x, v;
	x = xv->x;
	v = xv->v;
	xv->x = x + (k1->k1 + 2*k2->k1 + 2*k3->k1 + k4->k1)/6.;
	xv->v = v + (k1->k2 + 2*k2->k2 + 2*k3->k2 + k4->k2)/6.;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct K Force(struct K k, double x0, double v0, double dt, double omega2, double gamma, double f0, double omegaext, double t){
	k.k1 = v0*dt;
	k.k2 = (-omega2*sin(x0) - gamma*v0 + f0*cos(omegaext*t))*dt;
	return k;
}