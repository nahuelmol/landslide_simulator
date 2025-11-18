
#include <Eigen/Dense>
#include <iostream>
#include "Polygon.h"
#include "body.h"

using Eigen::MatrixXd;

Polygon::Polygon(int c) {
    this->ncorners = c;
    this->z = 0;
    MatrixXd m(c,2);
    this->corners = m;
}

void Polygon::set_corners(int z){
    std::cout << "setting corners coordinates here.. " << std::endl;
    this->z = z;
    this->corners = body_builder(z, this->ncorners); 
}

MatrixXd Polygon::get_corners() {
    return (this->corners);
}
