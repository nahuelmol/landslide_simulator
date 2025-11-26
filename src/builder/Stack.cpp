
#include <iostream>
#include "Polygon.h"
#include "Stack.h"

#include <Eigen/Dense>

using Eigen::MatrixXd;

Stack::Stack(int n, float delta, float z_top) {
    this->n = n;
    this->delta = delta;
    this->z_top = z_top;

    (this->locations).conservativeResize(n);

    MatrixXd m(n,1);
    this->PHI = m;
}

void Stack::add_polygon(Polygon* P, int i){
    float z = (i * (this->delta)) + (this->z_top);

    std::cout << "z:" << z << std::endl;
    std::cout << "i:" << i << std::endl;
    (this->locations)(i) = z;
    P->z = z;
}

void Stack::add_phi(float phi_m, int i){
    this->PHI(i,0) = phi_m; 
}


Polygon Stack::get_polygon(int i){
    //return only polygon's z value
    return (this->locations)[i];
}

