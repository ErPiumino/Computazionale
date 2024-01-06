//1D Random Walk with different probability for each pass
#include "Funzioni.h"

int main(int argv, char *argc[]){
    if(argv !=3){
		printf("\nInput must be: %s n(number of steps), Nsim (number of Simulations)\n", argc[0]);
		exit(1);
	}

    char *gnuplot_commands[300] = {
        "set terminal png size 1800,1500 enhanced",
        "set xlabel 't'",
        "set ylabel 'x(t)'",
        "set key outside title 'Legend' box 3",
        "set output 'Aleatorio.png'",
        "set multiplot layout 2,1",
        "end" 
    };

    FILE *gnu = popen("gnuplot -persist", "w");

    int i=0, rmax=1000, Nsim=atoi(argc[2]);
    char *c;
    //Write the commands to the pipe
    c = gnuplot_commands[i];
    do {
        fprintf(gnu, "%s\n", c);
        i++;
        c = gnuplot_commands[i];
    } while (strcmp(c,"end") != 0);
    fprintf(gnu, "\n");
    fprintf(gnu, "plot '-' title 'RW in random environment' with lines, \n");

    double* mean = RW(argv, argc, gnu);

    fprintf(gnu, "e\n");
    fprintf(gnu, "set xlabel 'ln(t)'\n");
    fprintf(gnu, "plot '-' title 'Behaviour of <x^2(t)>', \n");

    for (int j=0; j<Nsim; j++){
        double Mean = ((double) mean[j]/Nsim)/rmax;
        fprintf(gnu,"%lf %lf\n", log(j+1), Mean);
    }
    fprintf(gnu, "e\n");
    fprintf(gnu, "unset multiplot");
    pclose(gnu);
}