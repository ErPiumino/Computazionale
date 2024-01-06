#include "Funzioni.h"

int main(int argv, char *argc[]){
    if(argv !=4){
		printf("\nInput must be: x0(starting point), n(number of steps), Nsim(number of total simulations)\n");
		exit(1);
	}

    char *gnuplot_commands[300] = {
        "set terminal png size 1500,1800 enhanced",
        "set xlabel 't'",
        "set ylabel 'x(t)'",
        "set grid",
        "set key left top Left title 'Legend' box 3", 
        "set output 'RW.png'",
        "set multiplot layout 3,1 title 'Study of 1D Random Walk'",
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
    fprintf(gnu, "plot '-' title 'Random Walk 1 Dimension' with lines, \n");
    double **avg = RW(argv, argc, gnu);
    fprintf(gnu, "e\n");

    fprintf(gnu, "set ylabel '<x^2(t)>'\n");
    fprintf(gnu, "plot '-' with errorbars title '<x^2(t)> with error', \n");
    for(int i=0; i<atoi(argc[2]); i++){
        avg[0][i] /= atof(argc[3]);
        avg[1][i] /= atof(argc[3]);
        avg[1][i] -= avg[0][i] * avg[0][i];
        avg[1][i] = sqrt(avg[1][i] / (atoi(argc[3]) - 1));
        fprintf(gnu, "%i %lf %lf\n", i+1, avg[0][i], avg[1][i]);
    }
    fprintf(gnu, "e\n");
    fprintf(gnu, "set logscale x\n");
    fprintf(gnu, "set logscale y\n");
    fprintf(gnu, "plot x, ");
    fprintf(gnu, "'-' title '<x^2(t)>', \n");

    for(int i=0; i<atoi(argc[2]); i++){
        fprintf(gnu, "%i %lf\n", i+1, avg[0][i]);
    }
    fprintf(gnu, "e\n");

    fprintf(gnu, "unset multiplot \n");

    for(int i=0; i<2; i++){
        free(avg[i]);
    }
    free(avg);

    pclose(gnu);
}