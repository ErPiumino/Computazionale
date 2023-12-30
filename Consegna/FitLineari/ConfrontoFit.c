#include "Funzioni.h"

int main(int argv, char *argc[]){
    if(argv!=6){
        fprintf(stderr, "\nError, input must be: %s x0, v0, omega2, tmax, dt\n", argc[0]);
        exit(1);
    }

    char Method[5][25] = {"Eulero", 
        "EuleroCromer",
        "MidPoint", 
        "Verlet"};
    char Fun[5][5] = {"f(x)", "g(x)", "h(x)", "y(x)"};

    FILE *gnu = popen("gnuplot -persist", "w");
    gnuplot(gnu);
    ///////////////////////////////////////////////////////////////////////////
    FILE *out = fopen("Eulero.dat", "w+");
    Eulero(argv, argc, out);
    fclose(out);
    gnuplot1(gnu, Method[0], Fun[0]);
    ///////////////////////////////////////////////////////////////////////////
    out = fopen("EuleroCromer.dat", "w+");
    EuleroCromer(argv, argc, out);
    fclose(out);
    gnuplot1(gnu, Method[1], Fun[1]);
    ///////////////////////////////////////////////////////////////////////////
    out = fopen("MidPoint.dat", "w+");
    MidPoint(argv, argc, out);
    fclose(out);
    gnuplot1(gnu, Method[2], Fun[2]);
    ///////////////////////////////////////////////////////////////////////////
    out = fopen("Verlet.dat", "w+");
    Verlet(argv, argc, out);
    fclose(out);
    gnuplot1(gnu, Method[3], Fun[3]);
    fprintf(gnu, "unset multiplot\n");
    pclose(gnu);
}