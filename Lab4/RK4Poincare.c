//Runge-Kutta 4 using structs. Actual Physics problem: caotic Pendulum with study of dt variation and f0 variation
//Parametri per studio di forzante conformi a quelli su E-learning: 1.5707963267948965579989817342727 0 1 0.5 0.6666 0.9 200
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
void Python(double dat[5]);

int main(int argc, char **argv){
	Algoritmo(argc, argv); 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algoritmo (int argc, char **argv){
    struct Phase xv;
    struct K k1, k2, k3, k4;
	double omega2, omegaext, gamma, f0, tmax, dt, dat[5], T, Tmax;
	iterator k, i;
	int n, n1;
	FILE *fp;
	FILE *punti;
	if(argc !=8){
		printf("\nInput must be: theta0(deg) dtheta0/dt(rad/s) omega2(rad/s^2) gamma omegaext f0 tmax\n");
		exit(1);
	}
	//Lettura variabili e apertura file
	//xv.x = atof(argv[1]);//atof legge un float, atoi per gli int
	xv.x = M_PI/2.;//per essere precisi lo inserisco qui e ignoro l'inserimento da input, ma il risultato è identico se si approssima con abbastanza decimali
	xv.v = atof(argv[2]);
	omega2 = atof(argv[3]);
	gamma = atof(argv[4]);
	//omegaext = atof(argv[5]);
	omegaext = 2/3.;//stesso discorso di xv.x
	f0 = atof(argv[6]);
	tmax = atof(argv[7]);
	//Qui calcolo un Tmax diverso che si basa sulla ripetizione di circa 30.000 volte dell'algoritmo, in cui segno ogni 1000a volta (ovvero ogni volta che raggiungo il periodo)
	//posizione e velocità per fare la sezione di Poincarre, però il tmax che inserisco da input e che è molto più piccolo serve per salvare posizione e velocità per gli spazi delle fasi su
	//cui sovrapporre le sezioni, se salvassi questi dati per Tmax otterrei inutilmente un file di 500MB.
	T = (2.*M_PI)/omegaext;
	Tmax = T * 30000.;
	dt = T/1000.;
	for(k=0; k<5; k++){ //Eseguo cinque cicli perche' aumento la forzante
		n = tmax/dt;
		n1 = (int)Tmax/dt;
		char NomeFile[75];
		char NomeFilePunti[75];
		sprintf(NomeFile, "/workspaces/Computazionale2/Lab4/File/PendoloPoincareF0%.3lf.dat", f0); //Salvo i dati delle varie forzanti in file diversi
  		fp = fopen(NomeFile, "w");
		sprintf(NomeFilePunti, "/workspaces/Computazionale2/Lab4/File/PuntiPoincarreF0%.3lf.dat", f0); //Salvo i dati dei punti per Poincarre delle varie forzanti in file diversi
		punti = fopen(NomeFilePunti, "w+");
		fprintf(fp, "\t %.4lf \t %.4lf\n", xv.x, xv.v);
		//Passi algoritmo
		for(i=1; i<=n1; i++){
            Passo(&xv, k1, k2, k3, k4, omega2, omegaext, f0, gamma, dt, tmax, i);
			if((double)i*dt >= 5.*T && i<=n){ //salvo i dati dello spazio delle fasi solo se non ho superato le iterazioni minori di n1, calcolate con tmax, e solo se ho
			//superato un tempo di circa 5 volte il periodo in cui il pendolo si stabilizza e non è più caotico
            	fprintf(fp,"\t %.4lf \t %.4lf \n", xv.x, xv.v);
			}
			if((double)i*dt >= 5.*T){
				//Salvamento dati dei punti dove insiste la forzante, ovvero ogni 1000 passi siccome dt=T/1000
				if((i%1000) == 0){
					fprintf(punti, "%.10lf %.10lf\n", xv.x, xv.v);
				}
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
		xv.x=M_PI/2;
		xv.v = atof(argv[2]);
	}
	fclose(fp);
	fclose(punti);
	//Python(dat);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Passo (struct Phase *xv, struct K k1, struct K k2, struct K k3, struct K k4, double omega2, double omegaext, double f0, double gamma, double dt, double tmax, int i){
    double x, v;
	//Riporto la posizione nell'intervallo [-pi;pi] quando questa esce
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
//Queste righe non sono strettamente necessarie, ma di nuovo per rendere il codice il più generale possibile si basano sul fatto di riscrivere
//il python aggiornando i file da cui prendere i dati, i label e i titoli in base ai dati che venogno inseriti come input del file C
void Python(double dat[5]){
	FILE *py;
	FILE *py2;
	char label[10];
	char nomefile[10];
	sprintf(label, "f0");
	sprintf(nomefile,"F0");
	py=fopen("PoincareSpazioFasi.py", "w+");
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
	fprintf(py, "fig.suptitle('Sezioni di Poincare con Spazio delle fasi per varie $%s$', fontsize=25)\n \n", label);
	fprintf(py, "# Data per x(t) e v(t), spazio delle fasi\n");
	fprintf(py, "x1, v1 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloPoincare%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[0]);
	fprintf(py, "x2, v2 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloPoincare%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[1]);
	fprintf(py, "x3, v3 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloPoincare%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[2]);
	fprintf(py, "x4, v4 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloPoincare%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[3]);
	fprintf(py, "x5, v5 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloPoincare%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[4]);
	fprintf(py, "# Data per i punti per la sezione di Poincarre\n");
	fprintf(py, "xp1, vp1 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarre%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[0]);
	fprintf(py, "xp2, vp2 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarre%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[1]);
	fprintf(py, "xp3, vp3 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarre%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[2]);
	fprintf(py, "xp4, vp4 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarre%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[3]);
	fprintf(py, "xp5, vp5 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarre%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[4]);
	fprintf(py, "axs[0,0].scatter(x1, v1, color='blue', marker='.', s=0.001)\n");
	fprintf(py, "axs[0,0].scatter(xp1, vp1, color='red', label='Poincarre', marker='.', s=25)\n");
	fprintf(py, "axs[0,0].legend(loc='upper left', fontsize=8)\n");
	fprintf(py, "axs[0,0].title.set_text('$F0=%.2lf$')\n", dat[0]);
	fprintf(py, "axs[0,1].scatter(x2, v2, color='blue', marker='.',  s=0.001)\n");
	fprintf(py, "axs[0,1].scatter(xp2, vp2, color='red', label='Poincarre', marker='.', s=25)\n");
	fprintf(py, "axs[0,1].legend(loc='upper left', fontsize=8)\n");
	fprintf(py, "axs[0,1].title.set_text('$F0=%.2lf$')\n", dat[1]);
	fprintf(py, "axs[1,0].scatter(x3, v3, color='blue', marker='.',  s=0.001)\n");
	fprintf(py, "axs[1,0].scatter(xp3, vp3, color='red', label='Poincarre', marker='.', s=25)\n");
	fprintf(py, "axs[1,0].legend(loc='upper left', fontsize=8)\n");
	fprintf(py, "axs[1,0].title.set_text('$F0=%.2lf$')\n", dat[2]);
	fprintf(py, "axs[1,1].scatter(x4, v4, color='blue', marker='.',  s=0.001)\n");
	fprintf(py, "axs[1,1].scatter(xp4, vp4, color='red', label='Poincarre', marker='.', s=25)\n");
	fprintf(py, "axs[1,1].legend(loc='upper left', fontsize=8)\n");
	fprintf(py, "axs[1,1].title.set_text('$F0=%.2lf$')\n", dat[3]);
	fprintf(py, "axs[2,0].scatter(x5, v5, color='blue', marker='.',  s=0.001)\n");
	fprintf(py, "axs[2,0].scatter(xp5, vp5, color='red', label='Poincarre', marker='.', s=25)\n");
	fprintf(py, "axs[2,0].legend(loc='upper left', fontsize=8)\n");
	fprintf(py, "axs[2,0].title.set_text('$F0=%.2lf$')\n", dat[4]);
	fprintf(py, "axs[2,1].set_visible(False)\n");
	fprintf(py, "for ax in axs.flat:\n");
	fprintf(py, "\tax.set(xlabel='$\\\\theta$', ylabel='$d\\\\theta/dt$')\n");
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
	fprintf(py, "plt.savefig('/workspaces/Computazionale/Lab4/Grafici/PoincareSpazioFasi.pdf')\n");
	fclose(py);

	py2=fopen("Poincare.py", "w+");
	fprintf(py2, "# Importing libraries\n");
	fprintf(py2, "import matplotlib.pyplot as plt\n");
	fprintf(py2, "import numpy as np \n \n");
	fprintf(py2, "plt.title('Sezione di Poincarre per varie F0')\n");
	fprintf(py2, "plt.xlabel('$\\\\theta$')\n");
	fprintf(py2, "plt.ylabel('$d\\\\theta/dt$')\n");
	fprintf(py2, "xp1, vp1 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarre%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[0]);
	fprintf(py2, "xp2, vp2 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarre%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[1]);
	fprintf(py2, "xp3, vp3 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarre%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[2]);
	fprintf(py2, "xp4, vp4 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarre%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[3]);
	fprintf(py2, "xp5, vp5 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarre%s%.3lf.dat', usecols=(0, 1), unpack=True)\n", nomefile, dat[4]);
	fprintf(py2, "plt.scatter(xp1, vp1, color='darkslategrey', marker='.', s=50, label='$%s = %.2lf$')\n", nomefile, dat[0]);
	fprintf(py2, "plt.scatter(xp2, vp2, color='blue', marker='.', s=50, label='$%s = %.2lf$')\n", nomefile, dat[1]);
	fprintf(py2, "plt.scatter(xp3, vp3, color='green', marker='.', s=1, label='$%s = %.2lf$')\n", nomefile, dat[2]);
	fprintf(py2, "plt.scatter(xp4, vp4, color='skyblue', marker='.', s=50, label='$%s = %.2lf$')\n", nomefile, dat[3]);
	fprintf(py2, "plt.scatter(xp5, vp5, color='red', marker='.', s=1, label='$%s = %.2lf$')\n", nomefile, dat[4]);
	fprintf(py2, "plt.legend(loc='upper left')\n");
	fprintf(py2, "plt.savefig('/workspaces/Computazionale/Lab4/Grafici/Poincare.pdf')\n");
	fclose(py2);
}