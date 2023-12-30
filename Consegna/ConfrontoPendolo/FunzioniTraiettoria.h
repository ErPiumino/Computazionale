//File to store all the first and second order integration methods, in order to evaluate the differences
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <string.h>

typedef struct{
    double x; 
    double v; 
}Pos;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EuleroCromer(int argv, char *argc[], FILE *gnu){
	Pos pos1, pos2;
	pos1.x = atof(argc[1]);
	pos1.v = atof(argc[2]);
	double omega2 = atof(argc[3]), dt = atof(argc[5]);
	int tmax = atoi(argc[4]);
	int n = tmax/dt;
	fprintf(gnu, "0 %.2lf\n", pos1.x);
	for(int i=1; i<=n; i++){
		pos2.v=pos1.v - (omega2*(pos1.x)*dt);
		pos2.x=pos1.x + (pos2.v*dt);
		pos1.v=pos2.v;
		pos1.x=pos2.x;
		fprintf(gnu, "%.2lf %.2lf\n", i*dt, pos2.x);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Eulero(int argv, char *argc[], FILE *gnu){
	Pos pos1, pos2; //For x_n, x_n+1
	pos1.x = atof(argc[1]);
	pos1.v = atof(argc[2]);
	double omega2 = atof(argc[3]), dt = atof(argc[5]);
	int tmax = atoi(argc[4]);
	int n = tmax/dt;
	fprintf(gnu, "0 %.2lf\n", pos1.x);
	for(int i=1; i<=n; i++){
		pos2.x = pos1.x + (pos1.v*dt);
		pos2.v = pos1.v - (omega2*pos1.x*dt);
		pos1.x=pos2.x;
		pos1.v=pos2.v;
		fprintf(gnu, "%.2lf %.2lf\n",  i*dt, pos2.x);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MidPoint(int argv, char *argc[], FILE *gnu){
	Pos pos1, pos2; //For x_n, x_n+1
	pos1.x = atof(argc[1]);
	pos1.v = atof(argc[2]);
	double omega2 = atof(argc[3]), dt = atof(argc[5]);
	int tmax = atoi(argc[4]);
	int n = tmax/dt;
	fprintf(gnu, "0.00 %.2lf\n", pos1.x);
	for(int i=1; i<=n; i++){
		pos2.v = pos1.v - (omega2*(pos1.x)*dt);
		pos2.x = pos1.x + (((pos2.v+pos1.v)/2)*dt);
		pos1.v=pos2.v;		
		pos1.x=pos2.x;		
		fprintf(gnu, "%.2lf %.2lf \n", i*dt, pos2.x);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MidPointImplicito(int argv, char *argc[], FILE *gnu){
	Pos pos1, pos2; //For x_n, x_n+1
	pos1.x = atof(argc[1]);
	pos1.v = atof(argc[2]);
	double omega2 = atof(argc[3]), dt = atof(argc[5]);
	int tmax = atoi(argc[4]);
	int n = tmax/dt;
	fprintf(gnu, "0.00 %.2lf\n", pos1.x);
	for(int i=1; i<=n; i++){
		pos2.x = ((pos1.x*(1-(omega2*pow(dt,2))/(4))+ (dt*pos1.v))/(1+(omega2*pow(dt,2))/4));
		pos2.v = (pos1.v-(omega2*dt*((pos1.x+pos2.x)/2)));
		pos1.v = pos2.v;		
		pos1.x = pos2.x;
		fprintf(gnu, "%.2lf %.2lf \n", i*dt, pos2.x);
	}
}