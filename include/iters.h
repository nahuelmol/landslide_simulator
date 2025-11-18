#ifndef ITERS_H
#define ITERS_H

#include <Eigen/Dense>

using Eigen::VectorXd;

std::pair<float, float> a_b(VectorXd current, VectorXd next);
float sigma_set(float alpha, float beta, float z, VectorXd corner);

#endif //ITERS_H
