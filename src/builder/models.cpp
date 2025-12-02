
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

void least_squares(MatrixXd Data, MatrixXd PHI, VectorXd dens) {
    //comparing
    VectorXd g_c = PHI * dens;
    std::cout << "\ng_c:\n" << g_c << std::endl;
    VectorXd diffs = Data.col(3) - g_c;

    MatrixXd ATA = PHI.transpose() * PHI;
    VectorXd ATb = PHI.transpose() * diffs;
    VectorXd diffs_sigma = ATA.inverse() * ATb;
    VectorXd new_dens = dens + diffs_sigma;

    float BIAS_SSE = 0.5;
    float SSE = 0.0;

    if(SSE < BIAS_SSE) {
        std::cout << "\nSSE:" << SSE << std::endl;
        std::cout << "BIAS_SSE:" << BIAS_SSE << std::endl;
    }
    std::cout << "\nnewset:\n" << new_dens << std::endl;
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

    least_squares(Data, ST->PHI, densities);
}


