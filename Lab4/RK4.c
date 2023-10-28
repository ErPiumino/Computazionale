//Runge-Kutta 4 using structs. Actual Physics problem: caotic Pendulum with study of dt variation and f0 variation
//Parametri per studio di forzante conformi a quelli su E-learning: 1.5707963267948965579989817342727 0 1 0.5 0.66666666666667 0.9 100 0.001 1
//Parametri per studio di dt per fit: 1.5707963267948965579989817342727 0 1 0 0 0 100 0.01 2
//x(0)=pi/2 circa 1.5707963267948965579989817342727
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
void Passo(struct Phase *xv, struct K k1, struct K k2, struct K k3, struct K k4, double omega2, double omegaext, double f0, double gamma, double dt, double tmax, int i);
struct K Force(struct K k, double x0, double v0, double dt, double omega2, double gamma, double f0, double omegaext, double t);
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
	int n, fitchoice;
	FILE *fp;
	FILE *fit;
	if(argc !=10){
		printf("\nInput must be: theta0(deg) dtheta0/dt(rad/s) omega2(rad/s^2) gamma omegaext f0 tmax(s) dt(s) f0/fit \n(this last parameter is set to determine if the cycles of the algorithm are based on the increment of dt or of f0. Select 1 for f0 and 2 for fit. If 2 is set the input of f0 will be not considered).\n");
		exit(1);
	}
	//Lettura variabili e apertura file
	//xv.x = atof(argv[1]);//atof legge un float, atoi per gli int
	xv.x=M_PI/2.;
	xv.v = atof(argv[2]);
	omega2 = atof(argv[3]);
	gamma = atof(argv[4]);
	omegaext = atof(argv[5]);
	//omegaext = 2/3.;
	f0 = atof(argv[6]);
	tmax = atof(argv[7]);
	dt = atof(argv[8]);
	fitchoice = atof(argv[9]);
	if(fitchoice == 1 || fitchoice==2){}
	else{
		printf("\nError on the input line. Exiting...\n");
		exit(1);
	}
	if(fitchoice==2){
		fit=fopen("/workspaces/Computazionale/Lab4/File/fit.dat", "w");
	}
	for(k=0; k<5; k++){ //Eseguo cinque cicli perche' aumento la forzante o il dt
		n=tmax/dt;
		E0=Energy(xv, omega2);
		char NomeFile[65];
		if(fitchoice==1){
			sprintf(NomeFile, "/workspaces/Computazionale/Lab4/File/PendoloCaoticoF0%.3lf.dat", f0); //Salvo i dati delle varie forzanti in file diversi
		}
		if(fitchoice==2){
			sprintf(NomeFile, "/workspaces/Computazionale/Lab4/File/PendoloCaoticodt%.3lf.dat", dt); //Salvo i dati dei vari dt in file diversi
		}
  		fp = fopen(NomeFile, "w");
		fprintf(fp, "\t %.20lf \t %.20lf \t 0.00 \t %e \n", xv.x, xv.v, E0);
		//Passi algoritmo
		for(i=1; i<n; i++){
            Passo(&xv, k1, k2, k3, k4, omega2, omegaext, f0, gamma, dt, tmax, i);
            E=Energy(xv, omega2);
            fprintf(fp,"\t %.20lf \t %.20lf \t %.20lf \t %e\n", xv.x, xv.v, (double)i*dt, E);
			if(Emax<E){
				Emax=E; //Segno l'"Errore massimo" commesso in base al dt, altrimenti l'errore relativo sarebbe falsato
			}
		}
		if(fitchoice==2){
		fprintf(fit, "%.20lf %.20lf\n", dt, fabs((Emax-E0)/E0));//Salvo gli erorri relativi in base al dt su un altro file per evitare confusione
  			fclose(fp);
			dat[k] = dt;
			dt+=0.01;
		}
		if(fitchoice==1){
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
		}
		//xv.x = atof(argv[1]);
		xv.x=M_PI/2;
		xv.v = atof(argv[2]);
		omega2 = atof(argv[3]);
		gamma = atof(argv[4]);
		omegaext = atof(argv[5]);
		//omegaext = 2./3.;
		tmax = atof(argv[7]);
	}
	Python(dat, fitchoice);
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
	fprintf(py, "#plt.figure(figsize=(25, 50), dpi=80)\n");
	fprintf(py, "fig, axs = plt.subplots(2)\n"); 
	fprintf(py, "fig.suptitle('Pendolo forzato con RK4 per vari $%s$')\n \n", label);
	fprintf(py, "# Data per x(t) e e(t)\n");
	fprintf(py, "x1, y1, v1 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloCaotico%s%.3lf.dat', usecols=(2, 0, 1), unpack=True)\n", nomefile, dat[0]); 
	fprintf(py, "x2, y2, v2 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloCaotico%s%.3lf.dat', usecols=(2, 0, 1), unpack=True)\n", nomefile, dat[1]); 
	fprintf(py, "x3, y3, v3 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloCaotico%s%.3lf.dat', usecols=(2, 0, 1), unpack=True)\n", nomefile, dat[2]); 
	fprintf(py, "x4, y4, v4 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloCaotico%s%.3lf.dat', usecols=(2, 0, 1), unpack=True)\n", nomefile, dat[3]); 
	fprintf(py, "x5, y5, v5 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloCaotico%s%.3lf.dat', usecols=(2, 0, 1), unpack=True)\n", nomefile, dat[4]); 
	fprintf(py, "axs[0].plot(x1, y1, color='darkslategrey', label='$%s = %.3lf$', alpha=0.5, linewidth=0.5)\n", nomefile, dat[0]); 
	fprintf(py, "axs[0].plot(x2, y2, color='blue', label='$%s = %.3lf$', alpha=0.5, linewidth=0.5)\n", nomefile, dat[1]); 
	fprintf(py, "axs[0].plot(x3, y3, color='green', label='$%s = %.3lf$', alpha=0.5, linewidth=0.5)\n", nomefile, dat[2]); 
	fprintf(py, "axs[0].plot(x4, y4, color='skyblue', label='$%s = %.3lf$', alpha=0.5, linewidth=0.5)\n", nomefile, dat[3]); 
	fprintf(py, "axs[0].plot(x5, y5, color='red', label='$%s = %.3lf$', alpha=0.5, linewidth=0.5)\n", nomefile, dat[4]); 
	fprintf(py, "axs[0].set(xlabel='$t$', ylabel='$x(t)$')\n"); 
	fprintf(py, "axs[1].plot(y1, v1, color='darkslategrey', alpha=0.5, linewidth=0.5)\n"); 
	fprintf(py, "axs[1].plot(y2, v2, color='blue', alpha=0.5, linewidth=0.5)\n"); 
	fprintf(py, "axs[1].plot(y3, v3, color='green', alpha=0.5, linewidth=0.5)\n"); 
	fprintf(py, "axs[1].plot(y4, v4, color='skyblue', alpha=0.5, linewidth=0.5)\n"); 
	fprintf(py, "axs[1].plot(y5, v5, color='red', alpha=0.5, linewidth=0.5)\n"); 
	fprintf(py, "axs[1].set(xlabel='$x(t)$', ylabel='$v(t)$')\n"); 
	fprintf(py, "handles, labels = axs[-1].get_legend_handles_labels()\n"); 
	fprintf(py, "for ax in axs[:-1]:\n"); 
	fprintf(py, "\th, l=ax.get_legend_handles_labels()\n"); 
	fprintf(py, "\thandles += h\n"); 
	fprintf(py, "\tlabels += l\n"); 
	fprintf(py, "fig.legend(handles, labels, loc='upper right', bbox_to_anchor=(1, 0.75))\n"); 
	fprintf(py, "fig.subplots_adjust(right=0.7)\n");  
	fprintf(py, "plt.savefig('/workspaces/Computazionale/Lab4/Grafici/PendoloForzato.pdf')\n");
	fclose(py);
	if(fitchoice==2){
		FILE *fitpy;
		fitpy=fopen("fit.py", "w+");
		fprintf(fitpy, "#Importing libraries\n"); 
		fprintf(fitpy, "import matplotlib.pyplot as plt\n"); 
		fprintf(fitpy, "import numpy as np \n");
		fprintf(fitpy, "from scipy.optimize import curve_fit \n \n");
		fprintf(fitpy, "#Codice per il fit\n");
		fprintf(fitpy, "x,y=np.loadtxt('/workspaces/Computazionale/Lab4/File/fit.dat',unpack=True)\n");
		fprintf(fitpy, "log_x = np.fabs(np.log10(x))\n");
		fprintf(fitpy, "log_y = np.fabs(np.log10(y))\n");
		fprintf(fitpy, "params = np.polyfit(log_x, log_y, 1)\n");
		fprintf(fitpy, "#params = np.polyfit(x, y, 5)\n");
		fprintf(fitpy, "a = params[0]\n");
		fprintf(fitpy, "b = params[1]\n");
		fprintf(fitpy, "plt.loglog(x, y, label=f'Dati, m={a:.2f}', marker='x', color='Darkslategrey')\n");
		fprintf(fitpy, "#plt.loglog(x, 10**b * x**a, color='skyblue', label=f'm={a:.2f}', alpha=0.8)\n");
		fprintf(fitpy, "#plt.plot(x,a*x**5 + b*x**4 + c*x**3 + d*x**2 + e*x + f, color='skyblue', label='fit lineare', alpha=0.8)\n");
		fprintf(fitpy, "#plt.scatter(x, y, label='Dati', marker='x', color='Darkslategrey')\n");
		fprintf(fitpy, "#m=np.fabs((y-b*x**4-c*x**3-d*x**2-e*x-f)/(x**5))\n");
		fprintf(fitpy, "plt.xlabel('$dt$')\n");
		fprintf(fitpy, "plt.ylabel('$e$')\n");
		fprintf(fitpy, "#print('Il coff angolare:',m.mean())\n");
		fprintf(fitpy, "print('Il coff angolare:',a)\n");
		fprintf(fitpy, "plt.legend(loc='upper left')\n");
		fprintf(fitpy, "plt.savefig('/workspaces/Computazionale/Lab4/Grafici/FitPendoloCaotico.pdf')\n");
		fclose(fitpy);
	}
}