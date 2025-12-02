
#ifndef MODELS_H
#define MODELS_H

#include <vector>
#include <iostream>
#include <Eigen/Dense>

using Eigen::VectorXd;
using Eigen::MatrixXd;

float dimension(int i, int j);
float gen();
void initial_model(std::string elements, MatrixXd Data);
void least_squares(MatrixXd Data, MatrixXd dims, VectorXd dens, float alpha, float RMS_rel_prev);

#endif //MODELS_H
