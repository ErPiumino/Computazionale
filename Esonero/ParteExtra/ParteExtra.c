//Study of ODE's solution using Verlet Velocity method. Input to give: 0 0 0 1 0.1 0.01 100
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
struct K{
	double k1;
	double k2;
};

typedef int iterator;

void Algoritmo(int argc, char **argv);
void RK2(struct K kx1, struct K kx2, struct K ky1, struct K ky2, struct Position *r, struct Velocity *v, double gamma, double dt, double tmax, int i);
struct K Forcex (struct K k, double x0, double v0, double y0, double dt, double gamma, double t);
struct K Forcey (struct K k, double x0, double v0, double y0, double dt, double gamma, double t);
double ax(double x, double y, double v, double gamma);
double ay(double x, double y, double v, double gamma);
double Conservation(struct Position *r, struct Velocity *v);

int main(int argc, char **argv){
	Algoritmo(argc, argv); 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algoritmo (int argc, char **argv){
	struct Position r;
	struct Velocity v;
	struct K kx1, kx2, ky1, ky2;
	double tmax, dt, gamma, v0, theta;
	int n;
	iterator i;
	FILE *fp1, *fp2;
	if(argc !=8){
		printf("\nInput must be: x0 y0 theta v0 gamma dt tmax\n");
		exit(1);
	}
	//Reading the inzial parameters on the struct r0 and v0
	r.x = atof(argv[1]);
	r.y = atof(argv[2]);
	theta = atof(argv[3]);
	v0 = atof(argv[4]);
	gamma = atof(argv[5]);
	dt = atof(argv[6]);
	tmax = atof(argv[7]);
    v.x = v0 * cos(theta);
    v.y = v0 * sin(theta);
	n = tmax/dt;
	fp1 = fopen("ParteExtrax>0.dat", "w+");
	fp2 = fopen("ParteExtrax<0.dat", "w+");
	while(theta < M_PI/4. + 0.01){
		v0 = atof(argv[4]);
		v.x = v0 * cos(theta);
		v.y = v0 * sin(theta);
		while(v0<3.01){
			for(i=1; i<=n; i++){
				RK2(kx1, kx2, ky1, ky2, &r, &v, gamma, dt, tmax, i);
			}
			if(r.x>0){
				fprintf(fp1, "%.5lf \t %.5lf\n", v0, theta);
			}
			if(r.x<0){
				fprintf(fp2, "%.5lf \t %.5lf\n", v0, theta);
			}
			v0 += 0.001;
			r.x = atof(argv[1]);
			r.y = atof(argv[2]);
			v.x = v0 * cos(theta);
			v.y = v0 * sin(theta);
			if(v0 > 3.01){
				break;
			}
		}
		theta += 0.001;
		r.x = atof(argv[1]);
		r.y = atof(argv[2]);
		if(theta>M_PI/4. + 0.01){
			break;
		}
	}
	fclose(fp1);
	fclose(fp2);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RK2(struct K kx1, struct K kx2, struct K ky1, struct K ky2, struct Position *r, struct Velocity *v, double gamma, double dt, double tmax, int i){
	double x0, y0, vx0, vy0;
	x0 = r->x;
	y0 = r->y;
	vx0 = v->x;
	vy0 = v->y;
	kx1 = Forcex(kx1, r->x, v->x, r->y, dt, gamma, (double)(i-1)*dt);
	kx2 = Forcex(kx2, r->x+kx1.k1/2., v->x + kx1.k2/2., r->y+kx1.k1/2., dt, gamma, (double)(i-1)*dt+dt/2.);
	ky1 = Forcey(kx1, r->x, v->y, r->y, dt, gamma, (double)(i-1)*dt);
	ky2 = Forcey(kx2, r->x+kx1.k1/2., v->y + kx1.k2/2., r->y+kx1.k1/2., dt, gamma, (double)(i-1)*dt+dt/2.);

	r->x = x0 + kx2.k1;
	v->x = vx0 + kx2.k2;
	r->y = y0 + ky2.k1;
	v->y = vy0 + ky2.k2;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct K Forcex (struct K k, double x0, double v0, double y0, double dt, double gamma, double t){
	k.k1 = v0*dt;
	k.k2 = ax(x0, y0, v0, gamma)*dt;
	return k;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct K Forcey (struct K k, double x0, double v0, double y0, double dt, double gamma, double t){
	k.k1 = v0*dt;
	k.k2 = ay(x0, y0, v0, gamma)*dt;
	return k;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double ax(double x, double y, double v, double gamma){
	return 4*x*(1 - pow(x,2) - pow(y,2)) + x - gamma*v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double ay(double x, double y, double v, double gamma){
	return 4*y*(1 - pow(x,2) - pow(y,2)) - y - gamma*v;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double Conservation(struct Position *r, struct Velocity *v){
	return pow((r->x*r->x + r->y*r->y -1),2) + 0.5*(v->x*v->x + v->y*v->y);
}