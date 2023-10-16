#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void Pendolo(int argc, char **argv);

int main(int argc, char **argv){
	Pendolo(argc, argv); 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Pendolo (int argc, char **argv){
	double theta0, theta, v0, omega2, tmax, dt;
	double v, E0, E, Emax;
	int i, k, n;
	FILE *fp;
	FILE *fit;
	if(argc !=6){
		printf("\nInput must be: theta0 v0 omega2 tmax dt\n");
		exit(1);
	}
	theta0 = atof(argv[1]);//atof legge un float, atoi per gli int
	v0 = atof(argv[2]);
	omega2 = atof(argv[3]);
	tmax = atof(argv[4]);
	dt = atof(argv[5]);
	fit=fopen("FitPendolo.dat", "w");
	for(k=0; k<=3; k++){ //Eseguo tre cicli perche' aumento il dt ogni volta
		n=tmax/dt;
		E0=v0*v0+omega2*theta0*theta0;
		char NomeFile[20];
		sprintf(NomeFile, "Pendolo%.4lf.dat", dt); //Salvo i dati dei vari dt in file diversi
  		fp = fopen(NomeFile, "w");
		fprintf(fp, "\t %.2lf \t %.2lf \t 0.00 \t %.2lf\n", theta0, v0, E0);
		for(i=1; i<=n; i++){
            theta=theta0+(v0*dt)-((0.5)*omega2*sin(theta0)*pow(dt,2));
            v=v0-(omega2*(theta0))+((theta)*(0.5)*dt);
			theta0=theta;
			v0=v;
			E=(v*v)+(omega2*theta*theta);
			fprintf(fp,"\t %.2lf \t %.2lf \t %.2lf \t %lf\n", theta, v, i*dt, E);
			if(Emax<E){
				Emax=E; //Segno l'"Errore massimo" commesso in base al dt, altrimenti l'errore relativo sarebbe falsato
			}
		}
		fprintf(fit, "%lf %.20lf\n", dt, fabs((Emax-E0)/E0));//Salvo gli erorri relativi in base al dt su un altro file per evitare confusione
  		fclose(fp);
		dt+=0.0001; //Inizializzo le variabili e aumento dt
		theta0 = atof(argv[1]);
		v0 = atof(argv[2]);
		omega2 = atof(argv[3]);
	}
}