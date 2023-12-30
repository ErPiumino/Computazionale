//Parametri per studio di forzante conformi a quelli su E-learning: 1.5707963267948965579989817342727 0 1 0.5 0.66666667 0.9 200
#include "Funzioni.h"

int main(int argv, char *argc[]){
    if(argv!=8){
        fprintf(stderr, "\nError, input must be: %s theta0(deg) dtheta0/dt(rad/s) omega2(rad/s^2) gamma omegaext f0 tmax(s)\n", argc[0]);
        exit(1);
    }
    double omegaext = atof(argc[5]);
	double T = (2.*M_PI)/omegaext;
	double dt = T/1000.;

    char Force[5][6] = {"0.90", 
        "1.07", 
        "1.15", 
        "1.47", 
        "1.50"};

    char *gnuplot_commands[300] = {
        "set terminal png size 1800,1500 enhanced",
        "set xlabel 'x'",
        "set ylabel 'dx/dt'",
        "set xtics pi/2",
        "set ytics pi/2",
        "set format y '%.1Pπ'",
        "set format x '%.1Pπ'",
        "set xrange [-pi:pi]",
        "set grid",
        "set key outside title 'Legend' box 3",
        "set output 'Poincarre.png'",
        "set multiplot layout 3,2 title 'Phasespace and Poincarè for different f0'",
        "end" 
    };

    FILE *gnu = popen("gnuplot -persist", "w");

    int i=0;
    char *c;
    //Write the commands to the pipe
    c = gnuplot_commands[i];
    do {
        fprintf(gnu, "%s\n", c);
        i++;
        c = gnuplot_commands[i];
    } while (strcmp(c,"end") != 0);

    double f0 = atof(argc[6]);
    for(int k=0; k<5; k++){
        fprintf(gnu, "plot ");
        fprintf(gnu, "'-' title 'f0=%s' with points pt 7 ps 0.1 linecolor rgb 'blue', ", Force[k]);
        fprintf(gnu, "'-' title 'Poincarre' with points pt 7 ps 1 linecolor rgb 'red', ");
        fprintf(gnu, "\n");
        double** Poincarre = Poincare(argv, argc, gnu, f0);
        fprintf(gnu, "e\n");
        for(int j=1; j<=30000000; j++){
            if((double)j*dt >= 5.*T && (j%1000) == 0){
                fprintf(gnu, "%.10lf %.10lf\n", Poincarre[0][j-1], Poincarre[1][j-1]);
            }
        }
        fprintf(gnu, "e\n");
        f0 = F(k);
        Free(Poincarre, 2);
    }
    fprintf(gnu, "unset multiplot\n");
    pclose(gnu);
}