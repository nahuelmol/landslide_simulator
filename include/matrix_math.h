#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#include <Eigen/Dense>

using Eigen::MatrixXd;

std::vector<std::vector<float>> transpose(std::vector<std::vector<float>> D);
void inverse(MatrixXd D);

#endif //MATRIX_MATH_H
