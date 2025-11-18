
#include <vector>
#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;

void inverse(MatrixXd D){
    MatrixXd D_I = D.inverse();
    std::cout << "D_I:\n" << D_I << std::endl;
    bool is_simec = D.isApprox(D.transpose());
    if(is_simec) {
        std::cout << "is simectric" << std::endl;
    }
}

