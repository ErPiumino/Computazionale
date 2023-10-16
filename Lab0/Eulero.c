#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void passo(double x0, double v0, double w, double t, double d);

int main(){
	double x0, v0, w, t, d;
	scanf("%lf %lf %lf %lf %lf", &x0, &v0, &w, &t, &d);
	passo(x0, v0, w, t, d);
}
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
void passo(double x0, double v0, double w, double t, double d){
	double x, v, E, E0;
	int i, n;
	FILE *fp;
	n=t/d;
	E0=pow(v0,2) + (w*(pow(x0,2)));
	fp=fopen("Eulero.dat", "w");
	fprintf(fp, "%.2lf %.2lf 0 %.2lf\n", x0, v0, E0);
	for(i=1; i<=n; i++){
		x=x0 + (v0*d);
		v=v0 - (w*x0*d);
		x0=x;
		v0=v;
		E=pow(v0,2) + (w*(pow(x0,2)));
		fprintf(fp, "%.2lf %.2lf %.2lf %.2lf\n", x, v, i*d, E);
	}
	fclose(fp);
	printf("\nL'errore relativo e': %.2lf\n", fabs((E0-E)/E0));
}
