
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

void least_squares(MatrixXd Data, MatrixXd PHI, VectorXd dens, float alpha, float RMS_rel_prev) {
    //comparing
    VectorXd g_c = PHI * dens;
    //std::cout << "\ng_c:\n" << g_c << std::endl;
    VectorXd diffs = Data.col(3) - g_c;

    double RMS = std::sqrt(diffs.squaredNorm() / diffs.size());
    double RMS_rel = RMS / Data.col(3).norm();
    std::cout << "\nRMS_rel:\n" << RMS_rel << std::endl;

    MatrixXd ATA = PHI.transpose() * PHI;
    VectorXd ATb = PHI.transpose() * diffs;
    VectorXd diffs_sigma = ATA.inverse() * ATb;
    VectorXd new_dens = dens + (alpha) * diffs_sigma;

    float SSE = 0.05;

    if (RMS_rel < SSE){
        std::cout << "is okey" << std::endl;
        std::cout << "\nDensities:\n" << new_dens << std::endl;
    } else {
        if (RMS_rel < RMS_rel_prev) {
            alpha = alpha;
        } else {
            alpha = alpha / 2;
        }
        std::cout << "\nalpha:\n" << alpha << std::endl;
        least_squares(Data, PHI, new_dens, alpha, RMS_rel);
    }
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

    //std::cout << "\nDensities:\n" << densities << std::endl;
    //std::cout << "\nLocations:\n" << ST->locations << std::endl;

    least_squares(Data, ST->PHI, densities, 1.0, 1.0);
}


