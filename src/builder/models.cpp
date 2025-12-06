
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <Eigen/Dense>
#include "blocks.h"
#include "matrix_math.h"
#include "set_stack.h"
#include "export.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
const double G = 6.67430e-11;

void limpiar_ANSI() {
    printf("\033[2J"); // \033[2J: Borra toda la pantalla
    printf("\033[H");  // \033[H: Mueve el cursor a la esquina superior izquierda (1,1)
    fflush(stdout);   // Asegura que se envíe la salida inmediatamente
}

void limpiarConsola() {
#ifdef _WIN32 // Si es Windows
    system("cls");
#else // Si es Linux, macOS u otro (Unix-like)
    system("clear");
#endif
}

float dimension(int i, int j){
    //this should return 1/r^2
    float xdelta = 1;
    float z = 5;
    float x = std::abs(i-j) * xdelta;
    float d = sqrt(std::pow(x,2) + std::pow(z,2));
    float result = 1.0/(std::pow(d,2));
    return result;
}

void least_squares(MatrixXd Data, MatrixXd PHI, VectorXd dens, float prev_alpha, float RMS_rel_prev) {
    //comparing
    VectorXd g_c = PHI * dens;
    add_csv(g_c);
    VectorXd diffs = Data.col(3) - g_c;

    double RMS = std::sqrt(diffs.squaredNorm() / diffs.size());
    double RMS_rel = RMS / Data.col(3).norm();
    float SSE = 0.06;
    float alpha = 0.0;
    //std::cout << "\nRMS:\n" << RMS << std::endl;
    //std::cout << "\nRMS_rel_prev:\n" << RMS_rel_prev << std::endl;

    if (RMS_rel < SSE){
        std::cout << "\nRMS_rel:\n" << RMS_rel << std::endl;
        std::cout << "\nalpha:\n" << alpha << std::endl;

        std::cout << "is okey" << std::endl;
        std::cout << "\ng_c:\n" << g_c << std::endl;
        std::cout << "\nDensities:\n" << dens << std::endl;
        std::cout << "\nStoped Process:\n" << std::endl;
        alpha = prev_alpha * 0.99;
        double lambda = 1e-3;
        int n = PHI.cols();
        MatrixXd I_lamb = lambda * Eigen::MatrixXd::Identity(n,n);
        std::cout << "\nI_lambda:\n" << I_lamb << std::endl;
    } else {
        if(float(RMS_rel < float(RMS_rel_prev))){
            alpha = prev_alpha * 0.99;

            MatrixXd ATA = PHI.transpose() * PHI;
            VectorXd ATb = PHI.transpose() * diffs;
            VectorXd diffs_sigma = ATA.inverse() * ATb;
            VectorXd new_dens = dens + (alpha) * diffs_sigma;

            std::cout << "\033[2K\r";
            std::cout << "\033[A";
            std::cout << "\033[2K\r";

            std::cout << "RMS_rel:" << RMS_rel << "\n";
            std::cout << "alpha:" << alpha << "\r" << std::flush;
            least_squares(Data, PHI, new_dens, alpha, RMS_rel);
        }
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

    least_squares(Data, ST->PHI, densities, 0.1, 1.0);
}


