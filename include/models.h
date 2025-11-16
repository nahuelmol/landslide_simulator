
#ifndef MODELS_H
#define MODELS_H

#include <vector>
#include <iostream>
#include <Eigen/Dense>

using Eigen::VectorXd;

float dimension(int i, int j);
float gen();
void initial_model(int n, std::string elements, VectorXd L);
void least_squares(VectorXd L, VectorXd C);

#endif //MODELS_H
