
#include <Eigen/Dense>

using Eigen::VectorXd;

std::pair<float, float> a_b(VectorXd current, VectorXd next){
    float alpha = (next(0) - current(0)) / (next(1) - current(1));
    float beta = ((current(0)*next(1)) - (next(0)*current(1))) / (next(1) - current(1));
    return {alpha, beta};
}

float sigma_set(float alpha, float beta, float z, VectorXd corner){
    float num = z * (beta * corner(1) - alpha * std::pow(z,2));
    float den1 = corner(0) * ((1+std::pow(alpha,2)) * std::pow(z,2) + std::pow(beta,2));
    float t = std::pow(corner(0),2) + std::pow(corner(1),2) + std::pow(z,2);
    float den2 = (std::pow(alpha, 2) * std::pow(z,2) + std::pow(beta,2)) * std::sqrt(t);

    float den = den1 - den2;
    float result = num/den;
    return result;
}

