#include "FunzioniEnergia.h"

int main(int argv, char *argc[]){
    if(argv!=6){
        fprintf(stderr, "\nError, input must be: %s x0, v0, omega2, tmax, dt\n", argc[0]);
        exit(1);
    }
    char Method[5][25] = {"Eulero", 
        "EuleroCromer",
        "MidPoint", 
        "MidPoint Implicito"};

    char *gnuplot_commands[300] = {
        "set terminal png size 1500,1200 enhanced",
        "set title 'Evaluation of different integration methods, Physics problem: Pendulum",
        "set xlabel 't'",
        "set ylabel 'E(t)'",
        "set grid",
        "set key left top Left title 'Legend' box 3", 
        "set output 'ConfrontoEnergia.png'",
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
    fprintf(gnu, "set label 'x0=%.2lf' at screen 0.35, 0.92\n", atof(argc[1]));
    fprintf(gnu, "set label 'v0=%.2lf' at screen 0.35, 0.90\n", atof(argc[2]));
    fprintf(gnu, "set label 'w=%.2lf' at screen 0.35, 0.88\n", atof(argc[3]));
    fprintf(gnu, "set label 'dt=%.2lf' at screen 0.35, 0.86\n", atof(argc[5]));
    fprintf(gnu, "plot ");
    for (int i=0; i<4; i++){
        fprintf(gnu, "'-' title '%s' with lines, ", Method[i]);
    }
    fprintf(gnu, "\n");
    Eulero(argv, argc, gnu);
    fprintf(gnu, "e\n");
    EuleroCromer(argv, argc, gnu);
    fprintf(gnu, "e\n");
    MidPoint(argv, argc, gnu);
    fprintf(gnu, "e\n");
    MidPointImplicito(argv, argc, gnu);
    pclose(gnu);
}