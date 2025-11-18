
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <Eigen/Dense>
#include "blocks.h"
#include "matrix_math.h"
#include "set_stack.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
const double G = 6.67430e-11;

float dimension(int i, int j){
    //this should return 1/r^2
    float xdelta = 1;
    float z = 5;
    float x = std::abs(i-j) * xdelta;
    float d = sqrt(std::pow(x,2) + std::pow(z,2));
    float result = 1.0/(std::pow(d,2));
    return result;
}

void least_squares(VectorXd L, VectorXd C, MatrixXd dims, VectorXd dens) {
    //comparing
    VectorXd LSE(L.size());
    float BIAS_SSE = 0.5;
    float SSE = 0.0;
    VectorXd modified_C(L.size());
    VectorXd diffs(L.size());
    for(int i = 0; i < int(L.size()); i++){
        float diff = L[i] - C[i];
        diffs(i) = diff;
        float E2 = std::pow(diff, 2);
        SSE = SSE + E2;
        LSE(i) = E2;
    }

    if(SSE < BIAS_SSE) {
        std::cout << "SSE:" << SSE << std::endl;
        std::cout << "BIAS_SSE:" << BIAS_SSE << std::endl;
    }


    MatrixXd ATA = dims.transpose() * dims;
    VectorXd ATb = dims.transpose() * diffs;
    VectorXd diffs_sigma = ATA.inverse() * ATb;

    VectorXd newset_dens = dens + diffs_sigma;
}

float gen() {
    srand(static_cast<unsigned int>(time(nullptr)));
    float n = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float result = n * 2.7;
    return result;
}

void initial_model(int n, std::string elements, VectorXd L) {
    if (elements == "polygons") {
        std::cout << "making Talwani approach" << std::endl;
        build_stack(n);
    } else if (elements == "prisms") {
        std::cout << "making prisms approach" << std::endl;
    }

    int cols = int(L.size());
    VectorXd calculated(cols);
    VectorXd densities(n);
    MatrixXd dimensions(n, cols);

    for (int j = 0; j<n; j++){
        float sigma = gen();
        densities(j) = sigma;
    }
    float aux = 0.0;
    for (int i = 0; i< int(L.size());i++){
        //Block BLOCK(i); for object oriented
        for(int j = 0; j < n; j++) {
            float d = dimension(i,j);
            float effect = G * densities[j] * d;
            dimensions(i,j) = d;
            aux = effect + aux;
        }
        calculated(i) = aux;
        aux = 0.0;
    }

    least_squares(L, calculated, dimensions, densities);
}


