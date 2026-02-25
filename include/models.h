
#ifndef MODELS_H
#define MODELS_H

#include <vector>
#include <iostream>
#include <Eigen/Dense>

using Eigen::VectorXd;
using Eigen::MatrixXd;

class Model {
public:

    std::string model_type;
    MatrixXd data;
    VectorXd calculated;
    VectorXd densities;
    MatrixXd dimensions;
    int i;
    int j;
    int L;

    Model(std::string model_type, MatrixXd data);
    //float dimension(int i, int j);
    float gen();
    void initial();
    void adjust(MatrixXd dims, VectorXd dens, float alpha, double RMS_rel_prev);
};

#endif //MODELS_H
