#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct{
    double x;
    double v;
}Pos;

typedef struct{
	double k1;
	double k2;
}K;

typedef struct{
    double E0;
    double E;
    double Emax;
}En;

K Force(K k, double x0, double v0, double dt, double omega2, double gamma, double f0, double omegaext, double t);
double Energy(Pos xv, double omega2);
void Passo (Pos *xv, K k1, K k2, K k3, K k4, double omega2, double omegaext, double f0, double gamma, double dt, double tmax, int i);
void PassoPoincare(Pos *xv, K k1, K k2, K k3, K k4, double omega2, double omegaext, double f0, double gamma, double dt, double tmax, int i);
void* array(int N, int size);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RK4 (int argv, char *argc[], double f0, FILE* gnu){
    Pos xv;
    K k1, k2, k3, k4;
    En E;
    xv.x = atof(argc[1]);
    xv.v = atof(argc[2]);
    double omega2 = atof(argc[3]), gamma = atof(argc[4]), omegaext = atof(argc[5]), tmax = atof(argc[7]), dt = atof(argc[8]);
    int n=tmax/dt;
    E.E0=Energy(xv, omega2);
    fprintf(gnu, "0.00 %.4lf\n", xv.x);
    //Passi algoritmo
    for(int i=1; i<n; i++){
        Passo(&xv, k1, k2, k3, k4, omega2, omegaext, f0, gamma, dt, tmax, i);
        E.E=Energy(xv, omega2);
        fprintf(gnu,"%.4lf %.4lf\n", (double)i*dt, xv.x);
        if(E.Emax<E.E){
            E.Emax=E.E;
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double** Poincare(int argv, char *argc[], FILE* gnu, double f0){
    Pos xv;
    K k1, k2, k3, k4;
    xv.x = atof(argc[1]);
    xv.v = atof(argc[2]);
    double omega2 = atof(argc[3]), gamma = atof(argc[4]), omegaext = atof(argc[5]), tmax = atof(argc[7]);
	double T = (2.*M_PI)/omegaext;
	double Tmax = T * 30000.;
	double dt = T/1000.;
    int n = tmax/dt;
    int n1 = (int)Tmax/dt;
    double **Poincarre=(double**)calloc(2, sizeof(double*)); 
    for(int i=0; i<2; i++) {
        Poincarre[i] = (double *) calloc(n1, sizeof(double));
    }
    fprintf(gnu, "%.4lf %.4lf\n", xv.x, xv.v);
    //Algorithm
    for(int i=1; i<=n1; i++){
        PassoPoincare(&xv, k1, k2, k3, k4, omega2, omegaext, f0, gamma, dt, tmax, i);
        if((double)i*dt >= 5.*T && i<=n){
            fprintf(gnu,"%.4lf %.4lf \n", xv.x, xv.v);
        }
        if((double)i*dt >= 5.*T && (i%1000) == 0){
            //Points where f0 insists
            Poincarre[0][i-1] = xv.x;
            Poincarre[1][i-1] = xv.v;
        }
    }
    return Poincarre;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double Energy(Pos xv, double omega2){
    return (xv.v*xv.v + 2.*omega2*(1.-cos(xv.x)));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Passo (Pos *xv, K k1, K k2, K k3, K k4, double omega2, double omegaext, double f0, double gamma, double dt, double tmax, int i){
    double x, v;
	x = xv->x;
	v = xv->v;
	k1 = Force(k1, x, v, dt, omega2, gamma, f0, omegaext, (double)(i-1)*dt);
	k2 = Force(k2, x+k1.k1/2., v+k1.k2/2., dt, omega2, gamma, f0, omegaext, (double)(i-1)*dt+dt/2.);
	k3 = Force(k3, x+k2.k1/2., v+k2.k2/2., dt, omega2, gamma, f0, omegaext, (double)(i-1)*dt+dt/2.);
	k4 = Force(k4, x+k3.k1, v+k3.k2, dt, omega2, gamma, f0, omegaext, (double)(i-1)*dt+dt);
	xv->x = x+(k1.k1 + 2.*k2.k1 + 2.*k3.k1 + k4.k1)/6.;
	xv->v = v+(k1.k2 + 2.*k2.k2 + 2.*k3.k2 + k4.k2)/6.;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
K Force(K k, double x0, double v0, double dt, double omega2, double gamma, double f0, double omegaext, double t){
	k.k1 = v0*dt;
	k.k2 = (-omega2*sin(x0) - gamma*v0 + f0*cos(omegaext*t))*dt;
	return k;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double F(int k){
    switch (k){
    case(0):
        return 1.07;
        break;
    case(1):
        return 1.15;
        break;
    case(2):
        return 1.47;
        break;
    case(3):
        return 1.5;
        break;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PassoPoincare(Pos *xv, K k1, K k2, K k3, K k4, double omega2, double omegaext, double f0, double gamma, double dt, double tmax, int i){
    double x, v;
	//Bringin back x in [-pi;pi] 
	if(xv->x >= M_PI){
		xv->x -= 2.*M_PI;
	}
	if(xv->x <= -M_PI){
		xv->x += 2.*M_PI;
	}
	x = xv->x;
	v = xv->v;
	k1 = Force(k1, x, v, dt, omega2, gamma, f0, omegaext, (double)(i-1)*dt);
	k2 = Force(k2, x+k1.k1/2., v+k1.k2/2., dt, omega2, gamma, f0, omegaext, (double)(i-1)*dt+dt/2.);
	k3 = Force(k3, x+k2.k1/2., v+k2.k2/2., dt, omega2, gamma, f0, omegaext, (double)(i-1)*dt+dt/2.);
	k4 = Force(k4, x+k3.k1, v+k3.k2, dt, omega2, gamma, f0, omegaext, (double)(i-1)*dt+dt);
	xv->x = x+(k1.k1 + 2.*k2.k1 + 2.*k3.k1 + k4.k1)/6.;
	xv->v = v+(k1.k2 + 2.*k2.k2 + 2.*k3.k2 + k4.k2)/6.;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Free(double **array, int n){
    for(int i=0; i<n; i++){
        free(array[i]);
    }
    free(array);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Bacini(int argv, char *argc[], FILE* gnu, double f0){
    Pos xv;
    K k1, k2, k3, k4;
    xv.x = -M_PI;
    xv.v = -M_PI;
    int j;

    double omega2 = atof(argc[1]), gamma = atof(argc[2]), omegaext = atof(argc[3]), dt = atof(argc[5]);
    double tmax;
    if(f0==1.07 || f0==1.15){
        tmax = 100;
    }
    else{
        tmax = 93.;
    }
    int n=tmax/dt;

    while(xv.x<M_PI){
        double x0j = xv.x;
        double v0j = xv.v;
        while(xv.v<M_PI){
            double x0jj = xv.x;
            double v0jj = xv.v;
            for(j=1; j<=n; j++){
                Passo(&xv, k1, k2, k3, k4, omega2, omegaext, f0, gamma, dt, tmax, j);
            }
            //Alla fine dei 100 secondi, stampo, aggiorno la velocita e ricomincio l'algoritmo per 100 secondi di una velocità aumentata di PI/500
            if(xv.v<0){
                //fprintf(gnu, "%.4lf %.4lf 1\n", x0jj, v0jj);
            }
            if(xv.v>=0){
                fprintf(gnu, "%.4lf %.4lf\n", x0jj, v0jj);
            }
            xv.x = x0jj;
            xv.v = v0jj;
            xv.v += M_PI/500.;
            if(xv.v > M_PI){
                break;
            }
            j=1;
        }
        //After updating 10.000 the velocity, I recall the previous saved values e I update the position
        xv.x = x0j;
        xv.v = v0j;
        xv.x += M_PI/500.;
        if(xv.x > M_PI){
            break;
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Biforcazione(int argv, char *argc[], FILE* gnu, int k){
    Pos xv;
    K k1, k2, k3, k4;
    double xcontrollo;
    double omega2 = atof(argc[2]), gamma = atof(argc[3]), omegaext = atof(argc[4]);
    double f0=0.9;
	double T = (2.*M_PI)/omegaext;
	double dt = T/100.;
	double Tmax = T * 450.;
	int n = Tmax/dt;
    while(f0<=1.51){
        xv.x = atof(argc[1]); 
        xv.v = (k*M_PI)/10;
        for(int i=1; i<n; i++){
            Passo(&xv, k1, k2, k3, k4, omega2, omegaext, f0, gamma, dt, Tmax, i);
            if((double)i*dt >= 5.*T && i<=n && (i%100) == 0){
                if(fabs(xcontrollo-xv.v)>0.001){
                    fprintf(gnu, "%lf %lf\n", f0, xv.v);
                    xcontrollo=xv.v;
                }
            }
        }
        f0 += 0.0001;
        if(f0>1.500000){
            break;
        }
    }
}