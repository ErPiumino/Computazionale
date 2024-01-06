//Parametri per studio di forzante conformi a quelli su E-learning: 1.5707963267948965579989817342727 1 0.5 0.66666666666667
#include "Funzioni.h"

int main(int argv, char *argc[]){
    if(argv!=5){
        fprintf(stderr, "\nError, input must be: %s theta0(deg) omega2(rad/s^2) gamma omegaext\n", argc[0]);
        exit(1);
    }

    char *gnuplot_commands[300] = {
        "set terminal png size 1500,1200 enhanced",
        "set title 'Bifurcation of dtheta/dt in respect to df0",
        "set xlabel 'f0'",
        "set ylabel 'dx/dt'",
        "set grid",
        "unset key",
        "set output 'Biforcazione.png'",
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
    for (int i=0; i<11; i++){
        fprintf(gnu, "'-' pt 7 ps 0.5, ");
    }
    fprintf(gnu, "\n");
    for(int k=0; k<11; k++){
        Biforcazione(argv, argc, gnu, k);
        fprintf(gnu, "e\n");
    }
    pclose(gnu);
}