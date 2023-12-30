//Parametri per studio di forzante conformi a quelli su E-learning: 1 0.5 0.66666667 1.07 0.01
#include "Funzioni.h"

int main(int argv, char *argc[]){
    if(argv!=6){
        fprintf(stderr, "\nError, input must be: %s omega2 gamma omegaext f0 dt\n", argc[0]);
        exit(1);
    }

    char Force[5][6] = {"0.90", 
        "1.07", 
        "1.15", 
        "1.47", 
        "1.50"};

    char *gnuplot_commands[300] = {
        "set terminal png size 1800,1500 enhanced",
        "set palette defined (1 'black', 2 'yellow')",
        "set xlabel 'x'",
        "set ylabel 'dx/dt'",
        "set xtics pi/2",
        "set ytics pi/2",
        "set format y '%.1Pπ'",
        "set format x '%.1Pπ'",
        "set xrange [-pi:pi]",
        "set yrange [-pi:pi]",
        "set key outside title 'Legend' box 3",
        "set output 'Bacini.png'",
        "set multiplot layout 2,2 title 'Basins of Attraction'",
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

    double f0 = atof(argc[4]);
    for(int k=1; k<5; k++){
        fprintf(gnu, "set object 1 rectangle from graph 0,0 to graph 1,1 behind fillcolor rgb 'black' fillstyle solid noborder\n");
        fprintf(gnu, "plot ");
        fprintf(gnu, "'-' title 'f0=%s' pt 7 ps 0.01 linecolor rgb 'yellow', ", Force[k]);
        fprintf(gnu, "\n");
        Bacini(argv, argc, gnu, f0);
        fprintf(gnu, "e\n");
        f0 = F(k);
    }
    fprintf(gnu, "unset multiplot\n");
    pclose(gnu);
}