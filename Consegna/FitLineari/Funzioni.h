//File to store all the first and second order integration methods, in order to evaluate the differences
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct{
    double x; 
    double v; 
}Pos;

typedef struct{
    double E0; 
    double E; 
    double Emax; 
}Energy;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EuleroCromer(int argv, char *argc[], FILE *gnu){
	Pos pos1, pos2;
	Energy E;
	double  dt = atof(argc[5]);
	double ddt=dt;
	for(int j=0; j<4; j++){//I need at least 4 points to evaluate the fit
		E.Emax=0;
		pos1.x = atof(argc[1]);
		pos1.v = atof(argc[2]);
		double omega2 = atof(argc[3]);
		int tmax = atoi(argc[4]);
		int n = tmax/dt;
		E.E0=pow(pos1.v,2) + (omega2*pow(pos1.x,2));
		for(int i=1; i<=n; i++){
			pos2.v=pos1.v - (omega2*(pos1.x)*dt);
			pos2.x=pos1.x + (pos2.v*dt);
			pos1.v=pos2.v;
			pos1.x=pos2.x;
			E.E = pow(pos1.v,2) + (omega2*(pow(pos1.x,2)));
			if(E.Emax<E.E){
				E.Emax=E.E;
			}
		}
		fprintf(gnu, "%lf %.20lf\n", fabs(log(dt)), fabs(log((E.Emax-E.E0)/E.E0)));
		dt += ddt;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Eulero(int argv, char *argc[], FILE *gnu){
	Pos pos1, pos2; //For x_n, x_n+1
	Energy E;
	double  dt = atof(argc[5]);
	double ddt = dt;
	for(int j=0; j<4; j++){
		E.Emax=0;
		pos1.x = atof(argc[1]);
		pos1.v = atof(argc[2]);
		double omega2 = atof(argc[3]);
		int tmax = atoi(argc[4]);
		int n = tmax/dt;
		E.E0=pow(pos1.v,2) + (omega2*(pow(pos1.x,2)));
		for(int i=1; i<=n; i++){
			pos2.x = pos1.x + (pos1.v*dt);
			pos2.v = pos1.v - (omega2*pos1.x*dt);
			pos1.x=pos2.x;
			pos1.v=pos2.v;
			E.E=pow(pos1.v,2) + (omega2*(pow(pos1.x,2)));
			if(E.Emax<E.E){
				E.Emax=E.E;
			}
		}
		fprintf(gnu, "%lf %.20lf\n", fabs(log(dt)), fabs(log((E.Emax-E.E0)/E.E0)));
		dt += ddt;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MidPoint(int argv, char *argc[], FILE *gnu){
	Pos pos1, pos2; //For x_n, x_n+1
	Energy E;
	double dt = atof(argc[5]);
	double ddt = dt;
	for(int j=0; j<4; j++){
		pos1.x = atof(argc[1]);
		pos1.v = atof(argc[2]);
		double omega2 = atof(argc[3]);
		int tmax = atoi(argc[4]);
		int n = tmax/dt;
		E.E0=pow(pos1.v,2) + (omega2*pow(pos1.x,2));
		for(int i=1; i<=n; i++){
			pos2.v = pos1.v - (omega2*(pos1.x)*dt);
			pos2.x = pos1.x + (((pos2.v+pos1.v)/2)*dt);
			pos1.v=pos2.v;		
			pos1.x=pos2.x;		
			E.E=pow(pos1.v,2) + (omega2*(pow(pos1.x,2)));
			if(E.Emax<E.E){
				E.Emax=E.E;
			}
		}
		fprintf(gnu, "%lf %.20lf\n", fabs(log(dt)), fabs(log((E.Emax-E.E0)/E.E0)));
		dt += ddt;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Verlet(int argv, char *argc[], FILE *gnu){
	Pos pos1, pos2; //For x_n, x_n+1
	Energy E;
	double dt = atof(argc[5]);
	double ddt = dt;
	for(int j=0; j<4; j++){
		pos1.x = atof(argc[1]);
		pos1.v = atof(argc[2]);
		double omega2 = atof(argc[3]);
		int tmax = atoi(argc[4]);
		int n = tmax/dt;
		E.E0 = pow(pos1.v,2) + (omega2*pow(pos1.x,2));
		for(int i=1; i<=n; i++){
			pos2.x=(pos1.v*dt)+pos1.x-(omega2*pos1.x*pow(dt,2)*0.5);
			pos2.v=pos1.v-((omega2*pos1.x+omega2*pos2.x)*0.5*dt);
			E.E=pow(pos1.v,2) + omega2*pow(pos1.x,2);
			pos1.x=pos2.x;
			pos1.v=pos2.v;
			if(E.Emax<E.E){
				E.Emax=E.E;
			}
		}
		fprintf(gnu, "%lf %.20lf\n", fabs(log(dt)), fabs(log((E.Emax-E.E0)/E.E0)));
		printf("%lf %.20lf\n", ((dt)), fabs(((E.Emax-E.E0)/E.E0)));
		dt += ddt;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gnuplot(FILE *gnu){
    char *gnuplot_commands[300] = {
        "set terminal png size 1500,1200 enhanced",
        //"set title 'Evaluation of different integration methods, Physics problem: Pendulum",
        "set xlabel 'ln(dt)'",
        "set ylabel 'ln(Errore relativo)'",
        "set grid",
        "set key left top Left title 'Legend' box 3", 
        "set output 'ConfrontoFit.png'",
        "set multiplot layout 2,2",
        "f(x) = m*x + b",
        "g(x) = m*x + b",
        "h(x) = m*x + b",
        "y(x) = m*x + b",
        "end" 
    };
    int i=0;
    char *c;
    //Write the commands to the pipe
    c = gnuplot_commands[i];
    do {
        fprintf(gnu, "%s\n", c);
        i++;
        c = gnuplot_commands[i];
    } while (strcmp(c,"end") != 0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gnuplot1(FILE *gnu, char method[100], char fun[100]){
	char function[100];
	char fit[100];
    char *gnuplot_commands[100] = {
		fit,
		function,
		//"set label sprintf(\"m = \%3.4f\",m) at 0.5,0.5",
        "end" 
    };
	sprintf(fit, "fit %s '%s.dat' via m,b", fun, method);
	sprintf(function, "plot '%s.dat' title '%s' pt 7 ps 0.6, %s title 'fit'", method, method, fun);
    int i=0;
    char *c;
    //Write the commands to the pipe
    c = gnuplot_commands[i];
    do {
        fprintf(gnu, "%s\n", c);
        i++;
        c = gnuplot_commands[i];
    } while (strcmp(c,"end") != 0);
}