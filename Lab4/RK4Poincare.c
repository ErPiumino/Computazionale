//Runge-Kutta 4 using structs. Actual Physics problem: caotic Pendulum with study of dt variation and f0 variation
//Parametri per studio di forzante conformi a quelli su E-learning: 1.5707963267948965579989817342727 0 1 0.5 0.6666 0.9 100 0.001 1
//x(0)=pi/2 circa 1.5707963267948965579989817342727
//v(0)=0
//omega2=1
//gamma=0.5
//omegaext=2/3. circa 0.66666666666666666666666666
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
void Passo(struct Phase *xv, struct K k1, struct K k2, struct K k3, struct K k4, double omega2, double omegaext, double f0, double gamma, double dt, double tmax, int i);
struct K Force(struct K k, double x0, double v0, double dt, double omega2, double gamma, double f0, double omegaext, double t);
double Energy(struct Phase xv, double omega2);
void Python(double dat[5]);

int main(int argc, char **argv){
	Algoritmo(argc, argv); 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algoritmo (int argc, char **argv){
    struct Phase xv;
    struct K k1, k2, k3, k4;
	double omega2, omegaext, gamma, f0, tmax, dt, E0, E, Emax, dat[5];
	iterator k, i;
	int n;
	FILE *fp;
	FILE *fit;
	FILE *punti;
	if(argc !=8){
		printf("\nInput must be: theta0(deg) dtheta0/dt(rad/s) omega2(rad/s^2) gamma omegaext f0 tmax(s) \n");
		exit(1);
	}
	//Lettura variabili e apertura file
	//xv.x = atof(argv[1]);//atof legge un float, atoi per gli int
	xv.x=M_PI/2.;
	xv.v = atof(argv[2]);
	omega2 = atof(argv[3]);
	gamma = atof(argv[4]);
	//omegaext = atof(argv[5]);
	omegaext = 2/3.;
	f0 = atof(argv[6]);
	tmax = atof(argv[7]);
	dt = (2.*M_PI/omegaext)/1000;
	for(k=0; k<5; k++){ //Eseguo cinque cicli perche' aumento la forzante o il dt
		n=tmax/dt;
		E0=Energy(xv, omega2);
		char NomeFile[50];
		char NomeFilePunti[50];
		sprintf(NomeFile, "PendoloPoincareF0%.3lf.dat", f0); //Salvo i dati delle varie forzanti in file diversi
  		fp = fopen(NomeFile, "w");
		fprintf(fp, "\t %.20lf \t %.20lf \t 0.00 \t %e \n", xv.x, xv.v, E0);
		//Passi algoritmo
		for(i=1; i<n; i++){
            Passo(&xv, k1, k2, k3, k4, omega2, omegaext, f0, gamma, dt, tmax, i);
            E=Energy(xv, omega2);
			if(i*dt >= 5.*2.*M_PI/omegaext){
            	fprintf(fp,"\t %.20lf \t %.20lf \t %.20lf \t %e\n", xv.x, xv.v, (double)i*dt, E);
				//Salvamento dati dei punti dove insiste la forzante (NON FUNZIONA)
				if(((int)(2.*M_PI/omegaext))%((int)(i*dt))==0){
					sprintf(NomeFilePunti, "PuntiPoincarreF0%.3lf.dat", f0); 
					punti = fopen(NomeFilePunti, "w+");
					fprintf(punti, "%.10lf %.10lf", xv.x, xv.v);
			}
			}
			if(Emax<E){
				Emax=E; //Segno l'"Errore massimo" commesso in base al dt, altrimenti l'errore relativo sarebbe falsato
			}
			//printf("x\tv\tf0\tOmega2\tgamma\tk1.k1\tk1.k2\n");
			//printf("%lf\t%lf\t%lf\t%lf\t%lf\t%.20lf\t%.20lf\n", xv.x, xv.v, f0, omega2, gamma, k1.k1, k1.k2); //printf di controllo
		}
		if(k==0){
			dat[k] = f0;
			f0=1.07;
		}
		if(k==1){
			dat[k] = f0;
			f0=1.15;
		}
		if(k==2){
			dat[k] = f0;
			f0=1.47;
		}
		if(k==3){
			dat[k] = f0;
			f0=1.50;
		}
		if(k==4){
			dat[k] = f0;
		}
		//xv.x = atof(argv[1]);
		xv.x=M_PI/2;
		xv.v = atof(argv[2]);
		omega2 = atof(argv[3]);
		gamma = atof(argv[4]);
		//omegaext = atof(argv[5]);
		omegaext = 2./3.;
		tmax = atof(argv[7]);
	}
	for(i=0; i>=n; i++){

	}
	Python(dat);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double Energy(struct Phase xv, double omega2){
    return (xv.v*xv.v + 2.*omega2*(1.-cos(xv.x)));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Passo (struct Phase *xv, struct K k1, struct K k2, struct K k3, struct K k4, double omega2, double omegaext, double f0, double gamma, double dt, double tmax, int i){
    double x, v;
	if(xv->x >= M_PI){
		xv->x -= 2.*M_PI;
	}
	if(xv->x <= -M_PI){
		xv->x += 2.*M_PI;
	}
	x = xv->x;
	v = xv->v;
	k1 = Force(k1, x, v, dt, omega2, gamma, f0, omegaext, (double)(i-1)*dt);
	k2 = Force(k2, x+k1.k1/2., v+k1.k2/2., dt, omega2, gamma, f0, omegaext, (double)(i-1)*dt+dt/2.);
	k3 = Force(k3, x+k2.k1/2., v+k2.k2/2., dt, omega2, gamma, f0, omegaext, (double)(i-1)*dt+dt/2.);
	k4 = Force(k4, x+k3.k1, v+k3.k2, dt, omega2, gamma, f0, omegaext, (double)(i-1)*dt+dt);
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Implementation of Python file based on the data received on the input line
void Python(double dat[5]){
	FILE *py;
	char label[10];
	char nomefile[10];
	sprintf(label, "f0");
	sprintf(nomefile,"F0");
	py=fopen("Poincare.py", "w+");
	fprintf(py, "# Importing libraries\n"); 
	fprintf(py, "import matplotlib.pyplot as plt\n"); 
	fprintf(py, "import numpy as np \n \n");
	fprintf(py, "#plt.figure(figsize=(25, 50), dpi=80)\n");
	fprintf(py, "fig, axs = plt.subplots(3,2)\n"); 
	fprintf(py, "fig.set_figwidth(15)\n"); 
	fprintf(py, "fig.set_figheight(15)\n"); 
	fprintf(py, "fig.suptitle('Sezioni di Poincare per varie $%s$')\n \n", label);
	fprintf(py, "# Data per x(t) e e(t)\n");
	fprintf(py, "x1, v1 = np.loadtxt('PendoloPoincare%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[0]); 
	fprintf(py, "x2, v2 = np.loadtxt('PendoloPoincare%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[1]); 
	fprintf(py, "x3, v3 = np.loadtxt('PendoloPoincare%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[2]); 
	fprintf(py, "x4, v4 = np.loadtxt('PendoloPoincare%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[3]); 
	fprintf(py, "x5, v5 = np.loadtxt('PendoloPoincare%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[4]); 
	fprintf(py, "xp1, vp1 = np.loadtxt('PuntiPoincarre%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[0]); 
	fprintf(py, "xp2, vp2 = np.loadtxt('PuntiPoincarre%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[1]); 
	fprintf(py, "axs[0,0].scatter(x1, v1, color='blue', label='$%s = %.3lf$', marker='.', s=0.001)\n", nomefile, dat[0]); 
	fprintf(py, "axs[0,0].scatter(xp1, vp1, color='red', label='$%s = %.3lf$', marker='.', s=100)\n", nomefile, dat[0]); 
	fprintf(py, "axs[0,0].legend(loc='upper left', fontsize=8)\n"); 
	fprintf(py, "axs[0,1].scatter(x2, v2, color='blue', label='$%s = %.2lf$', s=0.001)\n", nomefile, dat[1]); 
	fprintf(py, "axs[0,1].scatter(xp2, vp2, color='red', label='$%s = %.3lf$', marker='.', s=100)\n", nomefile, dat[0]); 
	fprintf(py, "axs[0,1].legend(loc='upper left', fontsize=8)\n");
	fprintf(py, "axs[1,0].scatter(x3, v3, color='blue', label='$%s = %.2lf$', s=0.001)\n", nomefile, dat[2]); 
	fprintf(py, "axs[1,0].legend(loc='upper left', fontsize=8)\n");
	fprintf(py, "axs[1,1].scatter(x4, v4, color='blue', label='$%s = %.2lf$', s=0.001)\n", nomefile, dat[3]); 
	fprintf(py, "axs[1,1].legend(loc='upper left', fontsize=8)\n");
	fprintf(py, "axs[2,0].scatter(x5, v5, color='blue', label='$%s = %.2lf$', s=0.001)\n", nomefile, dat[4]);  
	fprintf(py, "axs[2,0].legend(loc='upper left', fontsize=8)\n");
	fprintf(py, "axs[2,1].set_visible(False)\n");  
	fprintf(py, "for ax in axs.flat:\n");
	fprintf(py, "\tax.set(xlabel='x(t)', ylabel='v(t)')\n");;
	fprintf(py, "fig.subplots_adjust(left=0.1, bottom=0.1, right=0.9, top=0.9, wspace=0.4, hspace=0.4)\n");
	fprintf(py, "plt.savefig('Poincare.pdf')\n");
	fclose(py);
}