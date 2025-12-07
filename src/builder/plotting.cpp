
#include <cstdio>
#include <vector>
#include <cmath>
#include <iostream>

void plot() {
    FILE *gp = popen("gnuplot", "w");
    if (!gp) {
        std::cout << "something wrong" << std::endl;
    }
    fprintf(gp, "set terminal wxt size 600,400\n");
    fprintf(gp, "set title 'Sine Wave'\n");
    fprintf(gp, "plot '-' with lines\n");

    for (int i=0; i < 100;++i) {
        double x = i * 0.1;
        double y = sin(x);
        fprintf(gp, "%f %f\n", x, y);
    }
    fprintf(gp, "e\n");
    fflush(gp);
    pclose(gp);
}

