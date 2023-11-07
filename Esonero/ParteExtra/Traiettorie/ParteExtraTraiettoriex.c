//Study of ODE's solution using Verlet Velocity method. Input to give: 0 0 0.1 0.01 100
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

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
typedef double extreme;

void Algoritmo(int argc, char **argv);
void RK2(struct K kx1, struct K kx2, struct K ky1, struct K ky2, struct Position *r, struct Velocity *v, double gamma, double dt, double tmax, int i);
struct K Forcex (struct K k, double x0, double v0, double y0, double dt, double gamma, double t);
struct K Forcey (struct K k, double x0, double v0, double y0, double dt, double gamma, double t);
double ax(double x, double y, double v, double gamma);
double ay(double x, double y, double v, double gamma);
double Conservation(struct Position *r, struct Velocity *v);
void Python(double v0dat[8], double thetadat[8]);

int main(int argc, char **argv){
	int seed = time(NULL);
	srand48(seed);
	Algoritmo(argc, argv); 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Algoritmo (int argc, char **argv){
	struct Position r;
	struct Velocity v;
	struct K kx1, kx2, ky1, ky2;
	double tmax, dt, gamma, v0, theta, v0dat[8], thetadat[8];
	extreme v0m=1, v0M=3, thetam=0, thetaM=M_PI/4.; //Meaning v0min and v0Max for random number generation
	int n, j1, j2;
	iterator i, k;
	FILE *fp;
	if(argc !=6){
		printf("\nInput must be: x0 y0 gamma dt tmax\n");
		exit(1);
	}
	//Reading the inzial parameters on the struct r0 and v0
	r.x = atof(argv[1]);
	r.y = atof(argv[2]);
	gamma = atof(argv[3]);
	dt = atof(argv[4]);
	tmax = atof(argv[5]);
	n = tmax/dt;
	for(k=0; k<8; k++){ //Doing many cycles with random different initial conditions
		j1=0;
		j2=0;
		while(j1==0){
			v0=(drand48()*(v0M-v0m+1)+v0m);
			if(v0<1 || v0>3){
				continue;
			}
			else{
				j1++;
				break;
			}
		}
		while(j2==0){
			theta=(drand48()*(thetaM-thetam+1)+thetam);
			if(theta<0 || theta>M_PI/4.){
				continue;
			}
			else{
				j2++;
				break;
			}
		}
		r.x = atof(argv[1]);
		r.y = atof(argv[2]);
		v.x = v0 * cos(theta);
    	v.y = v0 * sin(theta);
		char NomeFile[50];
		sprintf(NomeFile, "TraiettoriaxV0=%.2lfTheta=%.2lf.dat", v0, theta);
		fp = fopen(NomeFile, "w+");
		for(i=1; i<=n; i++){
			RK2(kx1, kx2, ky1, ky2, &r, &v, gamma, dt, tmax, i);
			fprintf(fp, "%.5lf \t %.5lf \t %.5lf\n", (double)i*dt, r.x, r.y);
		}
		fclose(fp);
		v0dat[k] = v0;
		thetadat[k] = theta;
	}
	Python(v0dat, thetadat);
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
	ky1 = Forcey(ky1, r->x, v->y, r->y, dt, gamma, (double)(i-1)*dt);
	ky2 = Forcey(ky2, r->x+ky1.k1/2., v->y + ky1.k2/2., r->y+ky1.k1/2., dt, gamma, (double)(i-1)*dt+dt/2.);

	r->x = x0 + kx2.k1;
	r->y = y0 + ky2.k1;
	v->x = vx0 + kx2.k2;
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Python(double v0dat[10], double thetadat[10]){
	FILE *py1;
	py1=fopen("Traiettorie.py", "w+");
	fprintf(py1, "# Importing libraries\n");
	fprintf(py1, "import matplotlib.pyplot as plt\n");
	fprintf(py1, "import numpy as np \n\n");
	fprintf(py1, "fig, ax = plt.subplots(1,2)\n");
	fprintf(py1, "fig.set_figwidth(30)\n");
	fprintf(py1, "fig.set_figheight(15)\n");
	fprintf(py1, "# Data per x(t) e e(t)\n");
	fprintf(py1, "t1, x1, y1 = np.loadtxt('TraiettoriaxV0=%.2lfTheta=%.2lf.dat', usecols=(0, 1, 2), unpack=True)\n", v0dat[0], thetadat[0]);
	fprintf(py1, "t2, x2, y2 = np.loadtxt('TraiettoriaxV0=%.2lfTheta=%.2lf.dat', usecols=(0, 1, 2), unpack=True)\n", v0dat[1], thetadat[1]);
	fprintf(py1, "t3, x3, y3 = np.loadtxt('TraiettoriaxV0=%.2lfTheta=%.2lf.dat', usecols=(0, 1, 2), unpack=True)\n", v0dat[2], thetadat[2]);
	fprintf(py1, "t4, x4, y4 = np.loadtxt('TraiettoriaxV0=%.2lfTheta=%.2lf.dat', usecols=(0, 1, 2), unpack=True)\n", v0dat[3], thetadat[3]);
	fprintf(py1, "t5, x5, y5 = np.loadtxt('TraiettoriaxV0=%.2lfTheta=%.2lf.dat', usecols=(0, 1, 2), unpack=True)\n", v0dat[4], thetadat[4]);
	fprintf(py1, "t6, x6, y6 = np.loadtxt('TraiettoriaxV0=%.2lfTheta=%.2lf.dat', usecols=(0, 1, 2), unpack=True)\n", v0dat[5], thetadat[5]);
	fprintf(py1, "t7, x7, y7 = np.loadtxt('TraiettoriaxV0=%.2lfTheta=%.2lf.dat', usecols=(0, 1, 2), unpack=True)\n", v0dat[6], thetadat[6]);
	fprintf(py1, "t8, x8, y8 = np.loadtxt('TraiettoriaxV0=%.2lfTheta=%.2lf.dat', usecols=(0, 1, 2), unpack=True)\n", v0dat[7], thetadat[7]);
	fprintf(py1, "ax[0].plot(t1, x1, color='black', label='$V0=%.2lf, \\\\theta =%.2lf$', alpha=0.8, linewidth=1.5)\n", v0dat[0], thetadat[0]);
	fprintf(py1, "ax[0].plot(t2, x2, color='red', label='$V0=%.2lf, \\\\theta =%.2lf$', alpha=0.8, linewidth=1.5)\n", v0dat[1], thetadat[1]);
	fprintf(py1, "ax[0].plot(t3, x3, color='blue', label='$V0=%.2lf, \\\\theta =%.2lf$', alpha=0.8, linewidth=1.5)\n", v0dat[2], thetadat[2]);
	fprintf(py1, "ax[0].plot(t4, x4, color='grey', label='$V0=%.2lf, \\\\theta =%.2lf$', alpha=0.8, linewidth=1.5)\n", v0dat[3], thetadat[3]);
	fprintf(py1, "ax[0].plot(t5, x5, color='cyan', label='$V0=%.2lf, \\\\theta =%.2lf$', alpha=0.8, linewidth=1.5)\n", v0dat[4], thetadat[4]);
	fprintf(py1, "ax[0].plot(t6, x6, color='orange', label='$V0=%.2lf, \\\\theta =%.2lf$', alpha=0.8, linewidth=1.5)\n", v0dat[5], thetadat[5]);
	fprintf(py1, "ax[0].plot(t7, x7, color='green', label='$V0=%.2lf, \\\\theta =%.2lf$', alpha=0.8, linewidth=1.5)\n", v0dat[6], thetadat[6]);
	fprintf(py1, "ax[0].plot(t8, x8, color='magenta', label='$V0=%.2lf, \\\\theta =%.2lf$', alpha=0.8, linewidth=1.5)\n", v0dat[7], thetadat[7]);
	fprintf(py1, "ax[0].set(xlabel='t(s)', ylabel='x(t)')\n");
	fprintf(py1, "ax[1].plot(t1, y1, color='black', label='$V0=%.2lf, \\\\theta =%.2lf$', alpha=0.8, linewidth=1.5)\n", v0dat[0], thetadat[0]);
	fprintf(py1, "ax[1].plot(t2, y2, color='red', label='$V0=%.2lf, \\\\theta =%.2lf$', alpha=0.8, linewidth=1.5)\n", v0dat[1], thetadat[1]);
	fprintf(py1, "ax[1].plot(t3, y3, color='blue', label='$V0=%.2lf, \\\\theta =%.2lf$', alpha=0.8, linewidth=1.5)\n", v0dat[2], thetadat[2]);
	fprintf(py1, "ax[1].plot(t4, y4, color='grey', label='$V0=%.2lf, \\\\theta =%.2lf$', alpha=0.8, linewidth=1.5)\n", v0dat[3], thetadat[3]);
	fprintf(py1, "ax[1].plot(t5, y5, color='cyan', label='$V0=%.2lf, \\\\theta =%.2lf$', alpha=0.8, linewidth=1.5)\n", v0dat[4], thetadat[4]);
	fprintf(py1, "ax[1].plot(t6, y6, color='orange', label='$V0=%.2lf, \\\\theta =%.2lf$', alpha=0.8, linewidth=1.5)\n", v0dat[5], thetadat[5]);
	fprintf(py1, "ax[1].plot(t7, y7, color='green', label='$V0=%.2lf, \\\\theta =%.2lf$', alpha=0.8, linewidth=1.5)\n", v0dat[6], thetadat[6]);
	fprintf(py1, "ax[1].plot(t8, y8, color='magenta', label='$V0=%.2lf, \\\\theta =%.2lf$', alpha=0.8, linewidth=1.5)\n", v0dat[7], thetadat[7]);
	fprintf(py1, "ax[1].set(xlabel='t(s)', ylabel='y(t)')\n");
	fprintf(py1, "for ax in ax.flat:\n");
	fprintf(py1, "\tax.legend(loc='upper right', fontsize=25, bbox_to_anchor=(3, 0.68))\n");
	fprintf(py1, "\tax.xaxis.get_label().set_fontsize(25)\n");
	fprintf(py1, "\tax.yaxis.get_label().set_fontsize(25)\n");
	fprintf(py1, "\tax.tick_params(axis='both', which='major', labelsize=25)\n");
	fprintf(py1, "fig.subplots_adjust(right=0.78, wspace=0.3)\n");
	fprintf(py1, "plt.savefig('Traiettorie1.pdf')\n");
	fclose(py1);
}