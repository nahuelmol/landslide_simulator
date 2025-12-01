
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

void Polygon::set_phi(MatrixXd Data, int Li) {
    float aux = 0.0;
    float new_aux = 0.0;
    int m = 0;
    for (int i=0;i<this->ncorners;i++){
        m = i+1;
        if (m == (this->ncorners)) {
            m = 0;
        }
        std::pair<float, float> results = a_b(this->corners.row(i), this->corners.row(m));
        // SIGMA is the primitive

        float x = Data(Li,0);
        float y = Data(Li,1);
        float w = (Data(Li,2) - this->z);
        float out_cte = (x - results.first * y - results.second);
        float A = std::pow(results.first,2) + 1;
        float B = -2 * (results.first * (x-results.second) + y);
        float C = std::pow((x-results.second), 2) + std::pow(y,2) + std::pow(w,2);
        float delta = 4 * A * C - std::pow(B,2);

        float F = F_set(A, B, C, delta, corners.row(i));
        float F_next = F_set(A, B, C, delta, corners.row(m));
        float FINAL = out_cte * (F_next - F);
        new_aux = new_aux + FINAL;

        float SIGMA = sigma_set(results.first, results.second, this->z, corners.row(i));
        float SIGMA_next = sigma_set(results.first, results.second, this->z, corners.row(m));
        float result = (std::atan(SIGMA_next) - std::atan(SIGMA));
        aux = aux + result;
    }
    this->phi = new_aux;
}

MatrixXd Polygon::get_corners() {
    return (this->corners);
}
