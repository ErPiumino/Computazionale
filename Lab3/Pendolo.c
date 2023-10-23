//Pendolo usando Eulero-Cromer. Impossibile usare VerletVelocity perchè c'è la 
//possibilità di inserire il coefficiente di attrito beta

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct Phase{
    double x;
    double v;
};

void Pendolo(int argc, char **argv);
struct Phase Passo(struct Phase xv, double omega2, double dt, double tmax, double b);
double Energy(struct Phase xv, double omega2, double b);


int main(int argc, char **argv){
	Pendolo(argc, argv); 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Pendolo (int argc, char **argv){
    struct Phase xv;
	double omega2, tmax, dt, b;
	double E0, E, Emax;
	int k, i, n;
	FILE *fp;
	FILE *fit;
	if(argc !=7){
		printf("\nInput must be: theta0(deg) Omega2(rad/s) beta omega2(rad/s^2) tmax(s) dt(s). If you want to do the simulation of a simple pendulum without external force, just put b=0\n");
		exit(1);
	}
	xv.x = atof(argv[1]);//atof legge un float, atoi per gli int
	xv.v = atof(argv[2]);
	b = atof(argv[3]);
	omega2 = atof(argv[4]);
	tmax = atof(argv[5]);
	dt = atof(argv[6]);
	char NomeFile1[20];
	if(b==0){
		sprintf(NomeFile1, "fit.dat", dt); //Salvo i dati dei vari dt in file diversi
	}
	else{
		sprintf(NomeFile1, "fitSmorzato.dat", dt); //Salvo i dati dei vari dt in file diversi
	}
	fit=fopen(NomeFile1, "w");
	for(k=0; k<=3; k++){ //Eseguo tre cicli perche' aumento il dt ogni volta
		n=tmax/dt;
		E0=Energy(xv, omega2, b);
		char NomeFile[20];
		if(b==0){
			sprintf(NomeFile, "Pendolo%.3lf.dat", dt); //Salvo i dati dei vari dt in file diversi
		}
		else{
			sprintf(NomeFile, "PendoloSmorzato%.3lf.dat", dt); //Salvo i dati dei vari dt in file diversi
		}
  		fp = fopen(NomeFile, "w");
		fprintf(fp, "\t %.2lf \t %.2lf \t 0.00 \t %e\n", xv.x, xv.v, E0);
		for(i=1; i<=n; i++){
            xv = Passo(xv, omega2, dt, tmax, b);
            E=Energy(xv, omega2, b);
            fprintf(fp,"\t %.2lf \t %.2lf \t %.2lf \t %e\n", xv.x, xv.v, i*dt, E);
			if(Emax<E){
				Emax=E; //Segno l'"Errore massimo" commesso in base al dt, altrimenti l'errore relativo sarebbe falsato
			}
		}
		fprintf(fit, "%lf %.20lf\n", dt, fabs((Emax-E0)/E0));//Salvo gli erorri relativi in base al dt su un altro file per evitare confusione
  		fclose(fp);
		dt+=0.001; //Inizializzo le variabili e aumento dt
		xv.x = atof(argv[1]);
		xv.v = atof(argv[2]);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double Energy(struct Phase xv, double omega2, double b){
    double E;
    E=xv.v*xv.v + omega2*xv.x*xv.x -b*xv.v;
    return E;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Phase Passo(struct Phase xv, double omega2, double dt, double tmax, double b){
    double x0, v0;
    x0=xv.x;
    v0=xv.v;
	xv.v=v0 - omega2*sin(x0)*dt;
	xv.x=x0 + xv.v*dt;
	x0=xv.x;
	v0=xv.v;
    return xv;
}