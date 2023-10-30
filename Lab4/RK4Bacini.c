//Runge-Kutta 4 using structs. Actual Physics problem: caotic Pendulum with study of dt variation and f0 variation
//Parametri per studio di bacini conformi a quelli su E-learning: -3.1415926535 -3.1415926535 1 0.5 0.66666667 0.9 100 0.01
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
void Python(double dat[5]);

int main(int argc, char **argv){
	Algoritmo(argc, argv); 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algoritmo (int argc, char **argv){
    struct Phase xv;
    struct K k1, k2, k3, k4;
	double omega2, omegaext, gamma, f0, tmax, dt, dat[5], x0i, v0i, x0j, v0j, x0jj, v0jj;
	iterator k, i, j, ii, jj;
	int n, vsegno;
	FILE *fp;
	if(argc !=9){
		printf("\nInput must be: theta0(deg) dtheta0/dt(rad/s) omega2(rad/s^2) gamma omegaext f0 tmax dt\n");
		exit(1);
	}
	//Lettura variabili e apertura file
	//xv.x = atof(argv[1]);//atof legge un float, atoi per gli int
	xv.x=-M_PI;//per essere precisi lo inserisco qui e ignoro l'inserimento da input, ma il risultato è identico se si approssima con abbastanza decimali
	//xv.v = atof(argv[2]);
	xv.v = -M_PI;
	omega2 = atof(argv[3]);
	gamma = atof(argv[4]);
	//omegaext = atof(argv[5]);
	omegaext = 2/3.;//stesso discorso di xv.x
	f0 = atof(argv[6]);
	tmax = atof(argv[7]);//deve essere 100, sarebbe il tempo caratteristico
	dt = atof(argv[8]);
	n = tmax/dt;
	for(k=0; k<5; k++){ //Eseguo cinque cicli perche' aumento la forzante
		char NomeFile[75];
		sprintf(NomeFile, "/workspaces/Computazionale/Lab4/File/BaciniF0%.3lf.dat", f0); //Salvo i dati delle varie forzanti in file diversi
		fp = fopen(NomeFile, "w+");
		//Passi algoritmo, tre cicli for per tutte le combinazioni di theta e dtheta/dt (il terzo per arrivare ogni volta a t=100)
		while(xv.x<M_PI){
			x0j = xv.x;
			v0j = xv.v;
			while(xv.v<M_PI){
				x0jj = xv.x;
				v0jj = xv.v;
				for(jj=1; jj<=n; jj++){
					Passo(&xv, k1, k2, k3, k4, omega2, omegaext, f0, gamma, dt, tmax, jj);
				}
				//Alla fine dei 100 secondi, stampo, aggiorno la velocita e ricomincio l'algoritmo per 100 secondi di una velocità aumentata di PI/500
				if(xv.v<0){
					vsegno = 0;
				}
				if(xv.v>=0){
					vsegno = 1;
				}
				fprintf(fp, "%.4lf %.4lf %i\n", x0jj, v0jj, vsegno);
				xv.x = x0jj;
				xv.v = v0jj;
				xv.v += M_PI/100.;
				if(xv.v > M_PI){
					break;
				}
			}
			//Dopo che per 10.000 volte ho aggionrato la velocità, riporto i valori che avevo salvato all'inizio del ciclo i=1 e aumento la posizione, e faccio ricominciare tutto
			xv.x = x0j;
			xv.v = v0j;
			xv.x += M_PI/100.;
			if(xv.x > M_PI){
				break;
			}
		}
		//Aumento la forzante in base al ciclo per rispettare i parametri su E-learning, ma potenzialmente basta togliere gli if e aumentare con f0+= per rendere il 
		//codice il più generico possibile (motivo per cui ho lasciato il ciclo principale)
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
		//xv.v = atof(argv[2]);
		xv.x=-M_PI;
		xv.v=-M_PI;
	}
	fclose(fp);
	Python(dat);
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Implementation of Python file based on the data received on the input line
//Queste righe non sono strettamente necessarie, ma di nuovo per rendere il codice il più generale possibile si basano sul fatto di riscrivere
//il python aggiornando i file da cui prendere i dati, i label e i titoli in base ai dati che venogno inseriti come input del file C
void Python(double dat[5]){
	FILE *py;
	char label[10];
	char nomefile[10];
	sprintf(label, "f0");
	sprintf(nomefile,"F0");
	py=fopen("Bacini.py", "w+");
	fprintf(py, "# Importing libraries\n");
	fprintf(py, "import matplotlib as mat\n");
	fprintf(py, "import matplotlib.pyplot as plt\n");
	fprintf(py, "from matplotlib.ticker import FormatStrFormatter, FuncFormatter, MultipleLocator\n");
	fprintf(py, "import numpy as np \n \n");
	fprintf(py, "#plt.rcParams['axes.grid'] = True\n");
	fprintf(py, "#plt.figure(figsize=(25, 50), dpi=80)\n");
	fprintf(py, "fig, axs = plt.subplots(3,2)\n");
	fprintf(py, "fig.set_figwidth(15)\n");
	fprintf(py, "fig.set_figheight(15)\n");
	fprintf(py, "fig.suptitle('Bacini di attrazione per varie $%s$', fontsize=25)\n \n", label);
	fprintf(py, "# Data per x(t) e v(t), bacini\n");
	fprintf(py, "x1, v1 = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[0]);
	fprintf(py, "x2, v2 = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[1]);
	fprintf(py, "x3, v3 = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[2]);
	fprintf(py, "x4, v4 = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[3]);
	fprintf(py, "x5, v5 = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[4]);
	fprintf(py, "axs[0,0].scatter(x1, v1, color='blue', marker='.', s=0.001)\n");
	fprintf(py, "axs[0,0].legend(loc='upper left', fontsize=8)\n");
	fprintf(py, "axs[0,0].title.set_text('$F0=%.2lf$')\n", dat[0]);
	fprintf(py, "axs[0,1].scatter(x2, v2, color='blue', marker='.',  s=0.001)\n");
	fprintf(py, "axs[0,1].legend(loc='upper left', fontsize=8)\n");
	fprintf(py, "axs[0,1].title.set_text('$F0=%.2lf$')\n", dat[1]);
	fprintf(py, "axs[1,0].scatter(x3, v3, color='blue', marker='.',  s=0.001)\n");
	fprintf(py, "axs[1,0].legend(loc='upper left', fontsize=8)\n");
	fprintf(py, "axs[1,0].title.set_text('$F0=%.2lf$')\n", dat[2]);
	fprintf(py, "axs[1,1].scatter(x4, v4, color='blue', marker='.',  s=0.001)\n");
	fprintf(py, "axs[1,1].legend(loc='upper left', fontsize=8)\n");
	fprintf(py, "axs[1,1].title.set_text('$F0=%.2lf$')\n", dat[3]);
	fprintf(py, "axs[2,0].scatter(x5, v5, color='blue', marker='.',  s=0.001)\n");
	fprintf(py, "axs[2,0].legend(loc='upper left', fontsize=8)\n");
	fprintf(py, "axs[2,0].title.set_text('$F0=%.2lf$')\n", dat[4]);
	fprintf(py, "axs[2,1].set_visible(False)\n");
	fprintf(py, "for ax in axs.flat:\n");
	fprintf(py, "\tax.set(xlabel='$\\\\theta(0)$', ylabel='$d\\\\theta/dt(0)$')\n");
	fprintf(py, "\tax.xaxis.set_major_formatter(FuncFormatter(\n");
	fprintf(py, "\t\tlambda val,pos: '{:.0g}$\\pi$'.format(val/np.pi) if val !=0 else '0'\n");
	fprintf(py, "\t))\n");
	fprintf(py, "\tax.xaxis.set_major_locator(MultipleLocator(base=np.pi/2))\n");
	fprintf(py, "\tax.yaxis.set_major_formatter(FuncFormatter(\n");
	fprintf(py, "\t\tlambda val,pos: '{:.0g}$\\pi$'.format(val/np.pi) if val !=0 else '0'\n");
	fprintf(py, "\t))\n");
	fprintf(py, "\tax.yaxis.set_major_locator(MultipleLocator(base=np.pi/2))\n");
	fprintf(py, "\tax.grid()\n");
	fprintf(py, "\tax.set_axisbelow(True)\n");
	fprintf(py, "fig.subplots_adjust(left=0.1, bottom=0.1, right=0.9, top=0.9, wspace=0.4, hspace=0.4)\n");
	fprintf(py, "plt.savefig('/workspaces/Computazionale/Lab4/Grafici/Bacini.pdf')\n");
	fclose(py);
}