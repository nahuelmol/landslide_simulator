
#include <Eigen/Dense>
#include <iostream>
#include "Polygon.h"

using Eigen::MatrixXd;

Polygon::Polygon(int c) {
    this->ncorners = c;
    this->z = 0;
    MatrixXd m(c,2);
    this->corners = m;
}

void Polygon::set_corners(){
    std::cout << "here I should set corners (its coordinates)" << std::endl;
}

MatrixXd Polygon::get_corners() {
    return (this->corners);
}
