
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
    float alpha;
    float prev_alpha;
    MatrixXd PHI;
    float SSE;

    Model(std::string model_type, MatrixXd data, float prev_alpha);
    //float dimension(int i, int j);
    void initial();
    void adjust(double RMS_rel_prev);
};

#endif //MODELS_H
