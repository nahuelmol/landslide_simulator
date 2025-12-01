#ifndef ITERS_H
#define ITERS_H

#include <Eigen/Dense>

using Eigen::VectorXd;

std::pair<float, float> a_b(VectorXd current, VectorXd next);
float sigma_set(float alpha, float beta, float z, VectorXd corner);
float F_set(float A, float B, float C, float delta, VectorXd corner);

#endif //ITERS_H
