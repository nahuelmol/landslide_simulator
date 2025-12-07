
#include <cstdio>
#include <vector>
#include <cmath>
#include <iostream>
#include <thread>
#include <chrono>

void plot(std::string file) {
    FILE *gp = popen("gnuplot", "w");
    if (!gp) {
        std::cout << "something wrong" << std::endl;
    }
    fprintf(gp, "set terminal png\n");
    fprintf(gp, "set output 'output.png'\n");

    std::string order = "plot ";
    for (int i=2; i < 21;++i) {
        std::string current = "'" + file + "' using 1:" + std::to_string(i) + " with lines,\\\n";
        order = order + current;
    }

    order.pop_back();
    order.pop_back();
    order.pop_back();
    order = order + "\n";

    fprintf(gp, order.c_str());
    fprintf(gp, "unset output\n");
    fflush(gp);
    pclose(gp);
}

