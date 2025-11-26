
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
void least_squares(VectorXd L, VectorXd C);

#endif //MODELS_H
