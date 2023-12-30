//Runge-Kutta 4 using structs. Actual Physics problem: caotic Pendulum with study of dt variation and f0 variation
//Parametri per studio di bacini conformi a quelli su E-learning: -3.1415926535 -3.1415926535 1 0.5 0.66666667 1.07 100 0.01
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
void Python(double dat[4], double temp[4]);

int main(int argc, char **argv){
	Algoritmo(argc, argv); 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algoritmo (int argc, char **argv){
    struct Phase xv;
    struct K k1, k2, k3, k4;
	double omega2, omegaext, gamma, f0, tmax, dt, dat[4], temp[4], x0j, v0j, x0jj, v0jj;
	iterator k, jj;
	int n;
	FILE *fp;
	FILE *colore;
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
	for(k=0; k<4; k++){ //Eseguo quattro cicli perche' aumento la forzante, non includo f0=0.9 perchè
	//i bacini di attrazione vengono tutti neri, infatti non sono presenti nel file
		n = tmax/dt;
		char NomeFile[75];
		char NomeFileColore[75];
		sprintf(NomeFile, "/workspaces/Computazionale/Lab4/File/Bacini/BaciniF0%.3lfBlack.dat", f0); //Salvo i dati delle varie forzanti in file diversi
		sprintf(NomeFileColore, "/workspaces/Computazionale/Lab4/File/Bacini/BaciniF0%.3lfYellow.dat", f0); //Salvo i dati delle varie forzanti in file diversi
		fp = fopen(NomeFile, "w+");
		colore = fopen(NomeFileColore, "w+");
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
					fprintf(fp, "%.4lf\t%.4lf\n", x0jj, v0jj);
				}
				if(xv.v>=0){
					fprintf(colore, "%.4lf\t%.4lf\n", x0jj, v0jj);
				}
				xv.x = x0jj;
				xv.v = v0jj;
				xv.v += M_PI/500.; //andrebbe aumentato di pi/500 ma passiamo da un tempo di computazione di 10 minuti
				//a 30 circa (per forzante), un grafico con 100.000 punti e risoluzione dimezzata è più che abbastanza
				if(xv.v > M_PI){
					break;
				}
				jj=1;
			}
			//Dopo che per 10.000 volte ho aggiornato la velocità, riporto i valori che avevo salvato all'inizio del ciclo i=1 e aumento la posizione, e faccio ricominciare tutto
			xv.x = x0j;
			xv.v = v0j;
			xv.x += M_PI/500.;
			if(xv.x > M_PI){
				break;
			}
		}
		//Aumento la forzante in base al ciclo per rispettare i parametri su E-learning, ma potenzialmente basta togliere gli if e aumentare con f0+= per rendere il 
		//codice il più generico possibile (motivo per cui ho lasciato il ciclo principale)
		if(k==0){
			dat[k] = f0;
			temp[k] = tmax;
			f0=1.15;
		}
		if(k==1){
			dat[k] = f0;
			temp[k] = tmax;
			tmax=93.;
			f0=1.47;
		}
		if(k==2){
			dat[k] = f0;
			temp[k] = tmax;
			tmax=93.;
			f0=1.50;
		}
		if(k==3){
			temp[k] = tmax;
			dat[k] = f0;
		}
		//xv.x = atof(argv[1]);
		//xv.v = atof(argv[2]);
		xv.x=-M_PI;
		xv.v=-M_PI;
	}
	fclose(fp);
	Python(dat, temp);
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
void Python(double dat[4], double temp[4]){
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
	fprintf(py, "#plt.figure(figsize=(25, 50), dpi=80)\n");
	fprintf(py, "fig, axs = plt.subplots(2,2)\n");
	fprintf(py, "fig.set_figwidth(30)\n");
	fprintf(py, "fig.set_figheight(30)\n");
	fprintf(py, "fig.suptitle('Bacini di attrazione per varie $%s$', fontsize=35)\n \n", label);
	fprintf(py, "# Data per x(t) e v(t), bacini\n");
	fprintf(py, "x1black, v1black = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/Bacini%s%.3lfBlack.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[0]);
	fprintf(py, "x1yellow, v1yellow = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/Bacini%s%.3lfYellow.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[0]);
	fprintf(py, "x2black, v2black = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/Bacini%s%.3lfBlack.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[1]);
	fprintf(py, "x2yellow, v2yellow = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/Bacini%s%.3lfYellow.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[1]);
	fprintf(py, "x3black, v3black = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/Bacini%s%.3lfBlack.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[2]);
	fprintf(py, "x3yellow, v3yellow = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/Bacini%s%.3lfYellow.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[2]);
	fprintf(py, "x4black, v4black = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/Bacini%s%.3lfBlack.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[3]);
	fprintf(py, "x4yellow, v4yellow = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/Bacini%s%.3lfYellow.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[3]);
	fprintf(py, "axs[0,0].scatter(x1black, v1black, color='black', marker='.', s=2.5)\n");
	fprintf(py, "axs[0,0].scatter(x1yellow, v1yellow, color='yellow', marker='.', s=2.5)\n");
	fprintf(py, "axs[0,0].set_title('$F0=%.2lf, t^*=%.2lf$', fontsize=25)\n", dat[0], temp[0]);
	fprintf(py, "axs[0,1].scatter(x2black, v2black, color='black', marker='.', s=2.5)\n");
	fprintf(py, "axs[0,1].scatter(x2yellow, v2yellow, color='yellow', marker='.', s=2.5)\n");
	fprintf(py, "axs[0,1].set_title('$F0=%.2lf, t^*=%.2lf$', fontsize=25)\n", dat[1], temp[1]);
	fprintf(py, "axs[1,0].scatter(x3black, v3black, color='black', marker='.', s=2.5)\n");
	fprintf(py, "axs[1,0].scatter(x3yellow, v3yellow, color='yellow', marker='.', s=2.5)\n");
	fprintf(py, "axs[1,0].set_title('$F0=%.2lf, t^*=%.2lf$', fontsize=25)\n", dat[2], temp[2]);
	fprintf(py, "axs[1,1].scatter(x4black, v4black, color='black', marker='.', s=2.5)\n");
	fprintf(py, "axs[1,1].scatter(x4yellow, v4yellow, color='yellow', marker='.', s=2.5)\n");
	fprintf(py, "axs[1,1].set_title('$F0=%.2lf, t^*=%.2lf$', fontsize=25)\n", dat[3], temp[3]);
	fprintf(py, "for ax in axs.flat:\n");
	fprintf(py, "\tax.set(xlabel='$\\\\theta(0)$', ylabel='$d\\\\dot \\\\theta(0)$')\n");
	fprintf(py, "\tax.xaxis.get_label().set_fontsize(25)\n");
	fprintf(py, "\tax.yaxis.get_label().set_fontsize(25)\n");
	fprintf(py, "\tax.xaxis.set_major_formatter(FuncFormatter(\n");
	fprintf(py, "\t\tlambda val,pos: '{:.0g}$\\pi$'.format(val/np.pi) if val !=0 else '0'\n");
	fprintf(py, "\t))\n");
	fprintf(py, "\tax.xaxis.set_major_locator(MultipleLocator(base=np.pi/2))\n");
	fprintf(py, "\tax.yaxis.set_major_formatter(FuncFormatter(\n");
	fprintf(py, "\t\tlambda val,pos: '{:.0g}$\\pi$'.format(val/np.pi) if val !=0 else '0'\n");
	fprintf(py, "\t))\n");
	fprintf(py, "\tax.yaxis.set_major_locator(MultipleLocator(base=np.pi/2))\n");
	fprintf(py, "\tax.xlim=(-np.pi, np.pi)\n");
	fprintf(py, "\tax.ylim=(-np.pi, np.pi)\n");
	fprintf(py, "\tax.tick_params(axis='both', which='major', labelsize=25)\n");
	fprintf(py, "fig.subplots_adjust(left=0.1, bottom=0.1, right=0.9, top=0.9, wspace=0.4, hspace=0.4)\n");
	fprintf(py, "plt.savefig('/workspaces/Computazionale/Lab4/Grafici/Bacini.png')\n");
	fclose(py);
}