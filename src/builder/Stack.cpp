
#include <iostream>
#include "Polygon.h"
#include "Stack.h"

#include <Eigen/Dense>

using Eigen::MatrixXd;
const double G = 6.67430e-11;

Stack::Stack(int n, int L, float delta, float z_top) {
    this->n = n;
    this->delta = delta;
    this->z_top = z_top;

    (this->locations).conservativeResize(n);

    MatrixXd m(L,n);
    this->PHI = m;
}

void Stack::add_polygon(Polygon* P, int i){
    float z = (i * (this->delta)) + (this->z_top);

    (this->locations)(i) = z;
    P->z = z;
}

void Stack::add_phi(float phi_m, int i, int j, float z, float Pz){
    float esp = 1.0;
    float distance_z = (z - Pz);
    this->PHI(j,i) = G * (distance_z) * phi_m * (esp); 
}


Polygon Stack::get_polygon(int i){
    //return only polygon's z value
    return (this->locations)[i];
}

