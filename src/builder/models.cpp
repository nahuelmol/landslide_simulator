
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

void initial_model(std::string elements, MatrixXd Data) {
    Stack* ST;
    if (elements == "polygons") {
        std::cout << "\n----Talwani----\n" << std::endl;
        ST = build_stack(4, Data);
    } else if (elements == "prisms") {
        std::cout << "making prisms approach" << std::endl;
    }

    int L = int(Data.col(3).size());
    VectorXd calculated(L);
    VectorXd densities(ST->n);
    MatrixXd dimensions(ST->n, L);

    for (int j = 0; j<(ST->n); j++){
        float sigma = gen();
        densities(j) = sigma;
    }

    std::cout << "\nDensities:\n" << densities << std::endl;
    std::cout << "\nLocations:\n" << ST->locations << std::endl;
    std::cout << "PHI:\n" << ST->PHI << std::endl;
    /*
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
    */
}


