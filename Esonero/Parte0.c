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
void Verlet(struct Position *r, struct Position *r1, struct Velocity *v, double dt);

int main(int argc, char **argv){
	Algoritmo(argc, argv); 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algoritmo (int argc, char **argv){
	struct Position r, r1;
	struct Velocity v;
	double tmax, dt;
	int n;
	iterator i;
	if(argc !=7){
		printf("\nInput must be: x0 v0 vx0 vy0 dt tmax\n");
		exit(1);
	}
	r.x = atof(argv[1]);
	r.y = atof(argv[2]);
	v.x = atof(argv[3]);
	v.y = atof(argv[4]);
	dt = atof(argv[5]);
	tmax = atof(argv[6]);
	n = tmax/dt;
	for(i=1; i<=n; i++){
		printf("%.10lf \t %.10lf \t %.10lf\n", (double)i*dt, r.x, r.y);
		Verlet(&r, &r1, &v, dt);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Verlet(struct Position *r, struct Position *r1, struct Velocity *v, double dt){
	double x0, y0;
	x0 = r->x;
	y0 = r->y;
	r1->x = r->x + v->x*dt + (4*r->x*(1 - r->x*r->x - r->y*r->y))*0.5*dt*dt; //Per facilita' di nomenclatura x0=x_(n-1), x1=x_n e x=x_(n+1)
	r1->y = r->y + v->y*dt + (4*r->x*(1 - r->x*r->x - r->y*r->y))*0.5*dt*dt; 
	r->x = 2*x0 - r1->x - (4*r->x*(1 - r->x*r->x - r->y*r->y))*dt*dt;
	r->y = 2*y0 - r1->y - (4*r->x*(1 - r->x*r->x - r->y*r->y))*dt*dt;
	v->x = (r->x - r1->x)/(2*dt);
	v->y = (r->y - r1->y)/(2*dt);
	r1->x = x0;
	r1->y = y0;
}