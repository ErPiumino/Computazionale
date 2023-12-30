//Runge-Kutta 4 using structs. Actual Physics problem: caotic Pendulum with study of dt variation and f0 variation
//Parametri per studio di forzante conformi a quelli su E-learning: 1.5707963267948965579989817342727 0 1 0.5 0.66666666666667 0.9 100 0.001
#include "Funzioni.h"

int main(int argv, char *argc[]){
    if(argv!=9){
        fprintf(stderr, "\nError, input must be: %s theta0(deg) dtheta0/dt(rad/s) omega2(rad/s^2) gamma omegaext f0 tmax(s) dt(s)\n", argc[0]);
        exit(1);
    }

    char Force[5][5] = {"0.90", 
        "1.07",
        "1.15", 
        "1.47", 
        "1.50"};
    char *gnuplot_commands[300] = {
        "set terminal png size 1500,1200 enhanced",
        "set title 'Pendulum with external force using RK4",
        "set xlabel 't'",
        "set ylabel 'x(t)'",
        "set grid",
        "set key left top Left title 'Legend' box 3", 
        "set output 'PendoloForzato.png'",
        "end" 
    };

    FILE *gnu = popen("gnuplot -persist", "w");

    int i=0;
    char *c;
    // Write the commands to the pipe
    c = gnuplot_commands[i];
    do {
        fprintf(gnu, "%s\n", c);
        i++;
        c = gnuplot_commands[i];
    } while (strcmp(c,"end") != 0);
    fprintf(gnu, "plot ");
    for (int i=0; i<5; i++){
        fprintf(gnu, "'-' title 'f0=%s' with lines, ", Force[i]);
    }
    fprintf(gnu, "\n");
    double f0 = atof(argc[6]);
    for(int k=0; k<5; k++){
        RK4(argv, argc, f0, gnu);
        fprintf(gnu, "e\n");
        f0 = F(k);
    }
    pclose(gnu);
}