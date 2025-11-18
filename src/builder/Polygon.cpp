
#include <Eigen/Dense>
#include <iostream>
#include "Polygon.h"
#include "body.h"
#include "iters.h"

using Eigen::MatrixXd;

Polygon::Polygon(int c) {
    this->ncorners = c;
    this->z = 0.0;
    MatrixXd m(c,2);
    this->corners = m;
}

void Polygon::set_corners(Body* BODY){
    std::cout << "setting corners coordinates here.. " << std::endl;

    float t = 1.0 - (std::pow((this->z)-(BODY->z_top),2)) / (std::pow(BODY->a,2));
    float r = (BODY->b) * std::sqrt(t);
    float ang = 360.0/(this->ncorners);

    MatrixXd corners(this->ncorners,2);
    for(int i=0; i<(this->ncorners); i++){
        corners(i,0) = r * std::sin(i*ang);
        corners(i,1) = r * std::cos(i*ang);
    }

    this->corners = corners;
}

void Polygon::set_phi() {
    float aux = 0.0;
    int m = 0;
    for (int i=0;i<this->ncorners;i++){
        m = i+1;
        if (m == (this->ncorners)) {
            m = 0;
        }
        std::pair<float, float> results = a_b(this->corners.row(i), this->corners.row(m));
        float SIGMA = sigma_set(results.first, results.second, this->z, corners.row(i));
        float SIGMA_next = sigma_set(results.first, results.second, this->z, corners.row(m));
        float result = (std::atan(SIGMA_next) - std::atan(SIGMA));
        //std::cout << "corners: " << i << " -> " << m << std::endl;
        aux = aux + result;
    }
    this->phi = aux;
}

MatrixXd Polygon::get_corners() {
    return (this->corners);
}
