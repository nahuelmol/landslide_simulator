#include <iostream>
#include <cmath>
#include <Eigen/Dense>

using Eigen::MatrixXd;

const double MY_PI = 3.14159265358979323846;

MatrixXd body_builder(int z, int c) {
    double a = 10.0;
    double b = 6.0;
    double z_top = -2.5;

    auto inside = [&](double x, double y, double z)->bool {
        double v = (x*x + y*y) / (b*b) + ((z-z_top)*(z-z_top)) / (a*a);
        return v <= 1.0;
    };

    float t = 1.0 - ((z-z_top)*(z-z_top)) / (a*a);
    float r = b * std::sqrt(t);
    float ang = 360.0/c;

    MatrixXd corners(c,2);
    for(int i=0; i<c; i++){
        corners(i,0) = r * std::sin(i*ang);
        corners(i,1) = r * std::cos(i*ang);
    }
    return corners;
}

