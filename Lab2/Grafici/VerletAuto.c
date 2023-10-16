#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void VerletAuto(int argc, char **argv);

int main(int argc, char **argv){
	VerletAuto(argc, argv); 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VerletAuto(int argc, char **argv){
	double x0, v0, omega2, tmax, dt;
	double x, v, E0, E, Emax;
	int i, k, n;
	FILE *fp;
	FILE *fit;
	if(argc !=6){
		printf("\nInput must be: x0 v0 omega2 tmax dt\n");
		exit(1);
	}
	x0 = atof(argv[1]);//atof legge un float, atoi per gli int
	v0 = atof(argv[2]);
	omega2 = atof(argv[3]);
	tmax = atof(argv[4]);
	dt = atof(argv[5]);
	fit=fopen("fitAuto.dat", "w"); 
	for(k=0; k<=3; k++){//Eseguo tre cicli perche' aumento il dt ogni volta
		n=tmax/dt;
		E0=pow(v0,2) + (omega2*pow(x0,2));
		char NomeFile[20];
		sprintf(NomeFile, "VerletAuto%.3lf.dat", dt); //Salvo i dati dei vari dt in file diversi
  		fp = fopen(NomeFile, "w");
		fprintf(fp, "\t %.2lf \t %.2lf \t 0.00 \t %.2lf\n", x0, v0, E0);
		for(i=1; i<=n; i++){
			x=(v0*dt)+x0-(omega2*x0*pow(dt,2)*0.5);
			v=v0-((omega2*x0+omega2*x)*0.5*dt);
			E=pow(v0,2) + omega2*pow(x0,2);
			x0=x;
			v0=v;
			fprintf(fp, "\t %.2lf \t %.2lf \t %.2lf \t %lf\n", x, v, i*dt, E);
			if(Emax<E){
				Emax=E;//Segno l'"Errore massimo" commesso in base al dt, altrimenti l'errore relativo sarebbe falsato
			}
		}
		fprintf(fit, "%lf %.20lf\n", dt, fabs((Emax-E0)/E0));//Salvo gli erorri relativi in base al dt su un altro file per evitare confusione
  		fclose(fp);
		dt+=0.001;//Inizializzo le variabili e aumento dt
		x0 = atof(argv[1]);
		v0 = atof(argv[2]);
		omega2 = atof(argv[3]);
	}
}