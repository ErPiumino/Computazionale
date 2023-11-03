//Runge-Kutta 4 using structs. Actual Physics problem: caotic Pendulum with study of dt variation and f0 variation
//Parametri per studio di bacini conformi a quelli su E-learning: 1.5707963267948965579989817342727 1 0.5 0.66666667 0.90
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
void Passo(struct Phase *xv, struct K k1, struct K k2, struct K k3, struct K k4, double omega2, double omegaext, double f0, double gamma, double dt, double tmax, int jj);
struct K Force(struct K k, double x0, double v0, double dt, double omega2, double gamma, double f0, double omegaext, double t);

int main(int argc, char **argv){
	Algoritmo(argc, argv); 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algoritmo (int argc, char **argv){
    struct Phase xv;
    struct K k1, k2, k3, k4;
	double omega2, omegaext, gamma, f0, dt, T, Tmax;
	iterator k, i;
	int n;
	FILE *fp;
	if(argc !=6){
		printf("\nInput must be: theta0(deg) omega2(rad/s^2) gamma omegaext f0\n");
		exit(1);
	}
	//Lettura variabili e apertura file
	//xv.x = atof(argv[1]);//atof legge un float, atoi per gli int
	xv.x=M_PI/2;//per essere precisi lo inserisco qui e ignoro l'inserimento da input, ma il risultato è identico se si approssima con abbastanza decimali
	//xv.v = atof(argv[2]);
	omega2 = atof(argv[2]);
	gamma = atof(argv[3]);
	//omegaext = atof(argv[5]);
	omegaext = 2/3.;//stesso discorso di xv.x
	f0 = atof(argv[5]);
	T = (2.*M_PI)/omegaext;
	dt = T/100.;
	Tmax = T * 450.;
	n = Tmax/dt;
	for(k=0; k<11; k++){ //Eseguo dieci cicli per l'accelerazione
		double xcontrollo;
		xv.x=M_PI/2.;
		xv.v = (k*M_PI)/10;
		f0=0.9;
		char NomeFile[100];
		sprintf(NomeFile, "/workspaces/Computazionale/Lab4/File/Biforcazione/BiforcazioneK%i.dat", k); //Salvo i dati delle varie forzanti in file diversi
		fp = fopen(NomeFile, "w+");
		while(f0<=1.51){
			xv.x=M_PI/2.;
			xv.v = (k*M_PI)/10;
			for(i=1; i<n; i++){
				Passo(&xv, k1, k2, k3, k4, omega2, omegaext, f0, gamma, dt, Tmax, i);
				if((double)i*dt >= 5.*T && i<=n && (i%100) == 0){
					if(fabs(xcontrollo-xv.v)>0.001){
						fprintf(fp, "%lf\t%lf\n", f0, xv.v);
						xcontrollo=xv.v;
					}
				}
			}
			f0 += 0.0001;
			if(f0>1.500000){
				break;
			}
		}
	}
	fclose(fp);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Passo (struct Phase *xv, struct K k1, struct K k2, struct K k3, struct K k4, double omega2, double omegaext, double f0, double gamma, double dt, double tmax, int jj){
    double x, v;
	x = xv->x;
	v = xv->v;
	k1 = Force(k1, x, v, dt, omega2, gamma, f0, omegaext, (double)(jj-1)*dt);
	k2 = Force(k2, x+k1.k1/2., v+k1.k2/2., dt, omega2, gamma, f0, omegaext, (double)(jj-1)*dt+dt/2.);
	k3 = Force(k3, x+k2.k1/2., v+k2.k2/2., dt, omega2, gamma, f0, omegaext, (double)(jj-1)*dt+dt/2.);
	k4 = Force(k4, x+k3.k1, v+k3.k2, dt, omega2, gamma, f0, omegaext, (double)(jj-1)*dt+dt);
	xv->x = x+(k1.k1 + 2.*k2.k1 + 2.*k3.k1 + k4.k1)/6.;
	xv->v = v+(k1.k2 + 2.*k2.k2 + 2.*k3.k2 + k4.k2)/6.;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct K Force(struct K k, double x0, double v0, double dt, double omega2, double gamma, double f0, double omegaext, double t){
	k.k1 = v0*dt;
	k.k2 = (-omega2*sin(x0) - gamma*v0 + f0*cos(omegaext*t))*dt;
	return k;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////