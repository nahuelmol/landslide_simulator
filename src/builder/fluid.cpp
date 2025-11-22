#include <iostream>
#include <fstream>
#include <cmath>

double kernel(double r, double h){
    //cubic spline kernel
    double q = r/h;
    double alpha = 1.0 / h; // normalización 1D

    if(q >= 0.0 && q< 1.0) {
        return (alpha * (1.0 - 1.5*q*q + 0.75*q*q*q));
    } else if(q >= 1.0 && q < 2.0) {
        double t = 2.0 - q;
        return (alpha * (0.25 * t * t * t));
    } else {
        return 0.0;
    }
}

void implement() {
    std::ofstream out("kernel_data.txt");
    double h = 1.0;
    int N = 200;

    for (int i = 0; i<= N; ++i){
        double r = 2.0 * h * i /N;
        double W = kernel(r, h);
        out << r << "\t" << W << "\n";
    }
    out.close();
}


