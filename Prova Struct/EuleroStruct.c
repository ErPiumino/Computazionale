#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct Phase{
    double x;
    double v;
};

void Eulero(int argc, char **argv);
struct Phase Passo(struct Phase xv, double omega2, double dt, double tmax);
double Energy(struct Phase xv, double omega2);

int main(int argc, char **argv){
	Eulero(argc, argv); 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Eulero (int argc, char **argv){
    struct Phase xv;
	double omega2, tmax, dt;
	double E0, E, Emax;
	int k, i, n;
	FILE *fp;
	FILE *fit;
	if(argc !=6){
		printf("\nInput must be: x0 v0 omega2 tmax dt\n");
		exit(1);
	}
	xv.x = atof(argv[1]);//atof legge un float, atoi per gli int
	xv.v = atof(argv[2]);
	omega2 = atof(argv[3]);
	tmax = atof(argv[4]);
	dt = atof(argv[5]);
	fit=fopen("fit.dat", "w");
	for(k=0; k<=3; k++){ //Eseguo tre cicli perche' aumento il dt ogni volta
		n=tmax/dt;
		E0=Energy(xv, omega2);
		char NomeFile[20];
		sprintf(NomeFile, "Eulero%.4lf.dat", dt); //Salvo i dati dei vari dt in file diversi
  		fp = fopen(NomeFile, "w");
		fprintf(fp, "\t %.2lf \t %.2lf \t 0.00 \t %lf\n", xv.x, xv.v, E0);
		for(i=1; i<=n; i++){
            xv = Passo(xv, omega2, dt, tmax);
            E=Energy(xv, omega2);
            fprintf(fp,"\t %.2lf \t %.2lf \t %.2lf \t %lf\n", xv.x, xv.v, i*dt, E);
			if(Emax<E){
				Emax=E; //Segno l'"Errore massimo" commesso in base al dt, altrimenti l'errore relativo sarebbe falsato
			}
		}
		fprintf(fit, "%lf %.20lf\n", dt, fabs((Emax-E0)/E0));//Salvo gli erorri relativi in base al dt su un altro file per evitare confusione
  		fclose(fp);
		dt+=0.0001; //Inizializzo le variabili e aumento dt
		xv.x = atof(argv[1]);
		xv.v = atof(argv[2]);
		omega2 = atof(argv[3]);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double Energy(struct Phase xv, double omega2){
    double E;
    E=(xv.v*xv.v) + (omega2*xv.x*xv.x);
    return E;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Phase Passo(struct Phase xv, double omega2, double dt, double tmax){
    double x0, v0;
    x0=xv.x;
    v0=xv.v;
	xv.x=x0 + (v0*dt);
	xv.v=v0 - (omega2*x0*dt);
	x0=xv.x;
	v0=xv.v;
    return xv;
}
