//Runge-Kutta 4 using structs. Actual Physics problem: caotic Pendulum
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
struct Phase Passo(struct Phase xv, struct K k1, struct K k2, struct K k3, struct K k4, double omega2, double omegaext, double f0, double gamma, double dt, double tmax, int i);
struct K Force(double x0, double v0, double dt, double omega2, double gamma, double f0, double omegaext, double t);
double Energy(struct Phase xv, double omega2);
void Python(double dat[5], int fitchoice);

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
	int n, ciclo=1, fitchoice;
	FILE *fp;
	FILE *fit;
	if(argc !=10){
		printf("\nInput must be: theta0(deg) dtheta0/dt(rad/s) omega2(rad/s^2) gamma omegaext f0 tmax(s) dt(s) f0/fit \n(this last parameter is set to determine if the cycles of the algorithm are based on the increment of dt or of f0. Select 1 for f0 and 2 for fit. If 2 is set the input of f0 will be not considered).\n");
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
	fitchoice = atof(argv[9]);
	//printf("%lf\t%lf\t%lf\t%lf\t%lf", xv.x, xv.v, f0, omega2, gamma); //printf di controllo
	if(fitchoice == 1 || fitchoice==2){}
	else{
		printf("\nError on the input line. Exiting...");
		exit(1);
	}
	if(fitchoice==2){
		fit=fopen("fit", "w");
	}
	for(k=0; k<=5; k++){ //Eseguo cinque cicli perche' aumento la forzante o il dt
		n=tmax/dt;
		E0=Energy(xv, omega2);
		char NomeFile[50];
		if(fitchoice==1){
			sprintf(NomeFile, "PendoloCaoticoF0%.3lf.dat", f0); //Salvo i dati delle varie forzanti in file diversi
		}
		if(fitchoice==2){
			sprintf(NomeFile, "PendoloCaoticodt%.3lf.dat", f0); //Salvo i dati delle varie forzanti in file diversi
		}
  		fp = fopen(NomeFile, "w");
		fprintf(fp, "\t %.20lf \t %.20lf \t 0.00 \t %e \n", xv.x, xv.v, E0);
		//Passi algoritmo
		for(i=1; i<=n; i++){
            xv = Passo(xv, k1, k2, k3, k4, omega2, omegaext, f0, gamma, dt, tmax, i);
            E=Energy(xv, omega2);
            fprintf(fp,"\t %.20lf \t %.20lf \t %.20lf \t %e\n", xv.x, xv.v, (double)i*dt, E);
			if(Emax<E){
				Emax=E; //Segno l'"Errore massimo" commesso in base al dt, altrimenti l'errore relativo sarebbe falsato
			}
			printf("x\tv\tf0\tOmega2\tgamma\tk1.k1\tk1.k2\n");
			printf("%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", xv.x, xv.v, f0, omega2, gamma, k1.k1, k1.k2); //printf di controllo
		}
		if(fitchoice==2){
		fprintf(fit, "%.20lf %.20.20lf\n", dt, fabs((Emax-E0)/E0));//Salvo gli erorri relativi in base al dt su un altro file per evitare confusione
  			fclose(fp);
		}
		//Inizializzo le variabili e aumento forzante
		if(fitchoice==2){
			dt+=0.001;
			dat[ciclo-1] = dt;
		}
		if(fitchoice==1){
			if(ciclo==1){
				dat[ciclo-1] = f0;
			}
			if(ciclo==2){
				f0=1.07;
				dat[ciclo-1] = f0;
			}
			if(ciclo==3){
				f0=1.15;
				dat[ciclo-1] = f0;
			}
			if(ciclo==4){
				f0=1.47;
				dat[ciclo-1] = f0;
			}
			if(ciclo==5){
				f0=1.50;
				dat[ciclo-1] = f0;
			}
		}
		ciclo+=1;
		xv.x = atof(argv[1]);
		xv.v = atof(argv[2]);
	}
	Python(dat, fitchoice);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double Energy(struct Phase xv, double omega2){
    return (xv.v*xv.v + omega2*(1.-cos(xv.x)));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Phase Passo(struct Phase xv, struct K k1, struct K k2, struct K k3, struct K k4, double omega2, double omegaext, double f0, double gamma, double dt, double tmax, int i){
    double x0, v0;
	x0=xv.x;
	v0=xv.v;
	k1 = Force(x0, v0, dt, omega2, gamma, f0, omegaext, i*dt);
	k2 = Force(x0+k1.k1/2., v0+k1.k2/2., dt, omega2, gamma, f0, omegaext, i*dt+dt/2.);
	k3 = Force(x0+k2.k1/2., v0+k2.k2/2., dt, omega2, gamma, f0, omegaext, i*dt+dt/2.);
	k4 = Force(x0+k3.k1/2., v0+k3.k2/2., dt, omega2, gamma, f0, omegaext, i*dt+dt/2.);
	xv.x=x0+(k1.k1 + 2*k2.k1 + 2*k3.k1 + k4.k1)/6.;
	xv.v=v0+(k1.k2 + 2*k2.k2 + 2*k3.k2 + k4.k2)/6.;
    return xv;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct K Force(double x0, double v0, double dt, double omega2, double gamma, double f0, double omegaext, double t){
	struct K k;
	k.k1 = v0*dt;
	k.k2 = (-omega2*sin(x0)-gamma*v0+f0*cos(omegaext*t))*dt;
	return k;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Python(double dat[5], int fitchoice){
	FILE *py;
	char label[10];
	char nomefile[10];
	if(fitchoice==1){
		sprintf(label, "f0");
	}
	else{
		sprintf(label, "\Delta t");
	}
	if(fitchoice==1){
		sprintf(nomefile,"F0");
	}
	else{
		sprintf(nomefile,"dt");
	}
	py=fopen("Pendulum.py", "w+");
	fprintf(py, "# Importing libraries\n"); 
	fprintf(py, "import matplotlib.pyplot as plt\n"); 
	fprintf(py, "import numpy as np \n \n");
	fprintf(py, "plt.figure(figsize=(12, 26), dpi=80)\n");
	fprintf(py, "fig, axs = plt.subplots(2)\n"); 
	fprintf(py, "fig.suptitle('Pendolo smorzato con Eulero-Cromer per vari $\Delta t$')\n \n");
	fprintf(py, "# Data per x(t) e e(t)\n");
	fprintf(py, "x1, y1, e1 = np.loadtxt('PendoloCaotico%s%.3lf.dat', usecols=(2, 0, 3), unpack=True)\n", nomefile, dat[0]); 
	fprintf(py, "x2, y2, e2 = np.loadtxt('PendoloCaotico%s%.3lf.dat', usecols=(2, 0, 3), unpack=True)\n", nomefile, dat[1]); 
	fprintf(py, "x3, y3, e3 = np.loadtxt('PendoloCaotico%s%.3lf.dat', usecols=(2, 0, 3), unpack=True)\n", nomefile, dat[2]); 
	fprintf(py, "x4, y4, e4 = np.loadtxt('PendoloCaotico%s%.3lf.dat', usecols=(2, 0, 3), unpack=True)\n", nomefile, dat[3]); 
	fprintf(py, "x5, y5, e5 = np.loadtxt('PendoloCaotico%s%.3lf.dat', usecols=(2, 0, 3), unpack=True)\n", nomefile, dat[4]); 
	fprintf(py, "axs[0].plot(x1, y1, color='darkslategrey', label='$%s = %.3lf$', alpha=0.5)\n", nomefile, dat[0]); 
	fprintf(py, "axs[0].plot(x2, y2, color='blue', label='$%s = %.3lf$', alpha=0.5)\n", nomefile, dat[1]); 
	fprintf(py, "axs[0].plot(x3, y3, color='green', label='$%s = %.3lf$', alpha=0.5)\n", nomefile, dat[2]); 
	fprintf(py, "axs[0].plot(x4, y4, color='skyblue', label='$%s = %.3lf$', alpha=0.5)\n", nomefile, dat[3]); 
	fprintf(py, "axs[0].plot(x5, y5, color='red', label='$%s = %.3lf$', alpha=0.5)\n", nomefile, dat[4]); 
	fprintf(py, "axs[0].set(xlabel='$t$', ylabel='$x(t)$')\n"); 
	fprintf(py, "axs[1].plot(e1, y1, color='darkslategrey', label='$%s = %.3lf$', alpha=0.5)\n", nomefile, dat[0]); 
	fprintf(py, "axs[1].plot(e2, y2, color='blue', label='$%s = %.3lf$', alpha=0.5)\n", nomefile, dat[1]); 
	fprintf(py, "axs[1].plot(e3, y3, color='green', label='$%s = %.3lf$', alpha=0.5)\n", nomefile, dat[2]); 
	fprintf(py, "axs[1].plot(e4, y4, color='skyblue', label='$%s = %.3lf$', alpha=0.5)\n", nomefile, dat[3]); 
	fprintf(py, "axs[1].plot(e5, y5, color='red', label='$%s = %.3lf$', alpha=0.5)\n", nomefile, dat[4]); 
	fprintf(py, "axs[1].set(xlabel='$t$', ylabel='$E(t)$')\n"); 
	fprintf(py, "for ax in axs.flat:\n"); 
	fprintf(py, "\tax.legend()\n");
	fprintf(py, "\tax.ticklabel_format(useOffset=False)\n"); 
	fprintf(py, "axs[0].legend(loc='upper right')\n"); 
	fprintf(py, "plt.savefig('PendoloForzato.pdf')\n");
}