//Study of ODE's solution using Verlet Velocity method. Input to give: 1 0 1 1 0.01 100
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct Position{
	double x;
	double y;
};
struct Velocity{
	double x;
	double y;
};

typedef int iterator;

void Algoritmo(int argc, char **argv);
void Verlet(struct Position *r, struct Position *r0, struct Velocity *v, struct Velocity *v0, double dt, int i);
double Conservation(struct Position *r, struct Velocity *v);
double a(double x, double y);

int main(int argc, char **argv){
	Algoritmo(argc, argv); 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algoritmo (int argc, char **argv){
	struct Position r, r0;
	struct Velocity v, v0;
	double tmax, dt, E0, E, Emax, tcontrollo=0;
	int n, j=1;
	iterator i, k;
	FILE *fit, *fp, *ritorno;
	if(argc !=7){
		printf("\nInput must be: x0 y0 vx0 vy0 dt tmax\n");
		exit(1);
	}
	//Reading the inzial parameters on the struct r0 and v0
	r0.x = atof(argv[1]);
	r0.y = atof(argv[2]);
	v0.x = atof(argv[3]);
	v0.y = atof(argv[4]);
	dt = atof(argv[5]);
	tmax = atof(argv[6]);
	fit = fopen("fit.dat", "w+");
	ritorno = fopen("TempiRitorno.dat", "w+");
	for(k=0; k<4; k++){//4 iteration for every dt in order to make the linear fit
		n = tmax/dt;
		E0 = Conservation(&r0, &v0);
		char NomeFile[50];
		sprintf(NomeFile, "Parte0dt%.2lf.dat", dt);
		fp = fopen(NomeFile, "w+");
		fprintf(fp, "0.0000000000 \t %.10lf \t %.10lf \t %.10lf \n",r0.x, r0.y, E0);
		for(i=1; i<=n; i++){
			Verlet(&r, &r0, &v, &v0, dt, i);
			E = Conservation(&r, &v);
			fprintf(fp, "%.10lf \t %.10lf \t %.10lf \t %.10lf\n", (double)i*dt, r.x, r.y, E);
			if(Emax<E){
				Emax = E;
			}
			//Check to see if the point passes for the x axis
			if((r.x * r0.x)<0 && k==0){
				fprintf(ritorno, "%i \t %lf\n", j, i*dt-tcontrollo);
				j++;
				tcontrollo = i*dt;
			}
			//Update of the variables for next step
			r0.x = r.x;
			r0.y = r.y;
			v0.x = v.x;
			v0.y = v.y;
		}
		fclose(fp);
		fprintf(fit, "%.10lf \t %.10lf \n", dt, fabs((Emax-E0)/E0));
		dt+=0.01;
		r0.x = atof(argv[1]);
		r0.y = atof(argv[2]);
		v0.x = atof(argv[3]);
		v0.y = atof(argv[4]);
	}
	fclose(fit);
	fclose(ritorno);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Verlet(struct Position *r, struct Position *r0, struct Velocity *v, struct Velocity *v0, double dt, int i){
	r->x = r0->x + v0->x*dt + 0.5*( a(r0->x, r0->y) )*dt*dt; //Meaning x(t+dt), while x(t) and y(t) would be the parameters of r0
	r->y = r0->y + v0->y*dt + 0.5*( a(r0->y, r0->x) )*dt*dt; //Meaning x(t+dt)
	v->x = v0->x + 0.5*( a(r0->x, r0->y)  +  a(r->x, r->y) )*dt; 
	v->y = v0->y + 0.5*( a(r0->y, r0->x)  +  a(r->y, r->x) )*dt; 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function of acceleration, equal for both x and y since it is sufficient to change the inizial input of the function from a(x,y) to a(y,x)
double a(double x, double y){
	return 4*x*(1 - pow(x,2) - pow(y,2));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double Conservation(struct Position *r, struct Velocity *v){
	return pow((r->x*r->x + r->y*r->y -1),2) + 0.5*(v->x*v->x + v->y*v->y);
}