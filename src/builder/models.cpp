
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <Eigen/Dense>

#include "set_stack.h"
#include "export.h"
#include "models.h"
#include "utils.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
const double G = 6.67430e-11;

Model::Model(std::string model_type, MatrixXd data, float prev_alpha) {
    this->data = data;
    this->model_type = model_type;
    this->alpha = 0.0;
    this->SSE = 0.06;
    this->prev_alpha = prev_alpha;
    this->L = int((this->data).col(3).size());
    (this->calculated).resize(this->L);
}

void Model::adjust(double RMS_rel_prev) {
    VectorXd g_c = (this->PHI) * this->densities;
    //add_csv(g_c);
    VectorXd diffs = (this->data).col(3) - g_c;

    double RMS = std::sqrt(diffs.squaredNorm() / diffs.size());
    double RMS_rel = RMS / (this->data).col(3).norm();

    if (RMS_rel < SSE){
        std::cout << "\nRMS_rel:\n" << RMS_rel << std::endl;
        std::cout << "\nalpha:\n" << (this->prev_alpha) << std::endl;
        //std::cout << "\ng_c:\n" << g_c << std::endl;
        //std::cout << "\nDensities:\n" << dens << std::endl;
        (this->alpha) = (this->prev_alpha) * 0.99;
    } else {
        if(float(RMS_rel < float(RMS_rel_prev))){
            (this->alpha) = (this->prev_alpha) * 0.99;
            double lambda = 1e-3;
            int n = (this->PHI).cols();
            MatrixXd I_lamb = lambda * Eigen::MatrixXd::Identity(n,n);

            MatrixXd ATA = ((this->PHI).transpose() * (this->PHI));
            VectorXd ATb = (this->PHI).transpose() * diffs;
            VectorXd diffs_sigma = ATA.inverse() * ATb;
            this->densities = (this->densities) + (this->alpha) * diffs_sigma;

            limpiar_ANSI();
            std::cout << "RMS_rel:" << RMS_rel << "\n";
            std::cout << "alpha:" << (this->alpha) << "\n";

            this->adjust(RMS_rel);
        }
    }
}


void Model::initial() {
    Stack* ST;
    if ((this->model_type) == "polygons") {
        std::cout << "\n----Talwani----\n" << std::endl;
        ST = build_stack(4, this->data);
    } else if (model_type == "prisms") {
        std::cout << "making prisms approach" << std::endl;
    } else {
        std::cout << "not recognized model type" << std::endl;
    }

    //this->dimensions(ST->n, this->L);

    (this->densities).resize(ST->n);
    for (int j = 0; j<(ST->n); j++){
        (this->densities(j)) = gen();
    }

    //std::cout << "\nDensities:\n" << (this->densities) << std::endl;
    //std::cout << "\nLocations:\n" << ST->locations << std::endl;

    (this->PHI).resize((ST->PHI).rows(), (ST->PHI).cols());
    this->PHI = ST->PHI;
    this->adjust(1.0);
}

