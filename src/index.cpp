
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "models.h"
#include <Eigen/Dense>

using Eigen::VectorXd;
using Eigen::MatrixXd;

void navier_stokes_eq() {
    std::cout << "executing navier stokes eq"<< std::endl;
}

void euler_eq() {
    std::cout << "executing euler eq" << std::endl;
}

int main () {
    std::string elements = "polygons";
    VectorXd L(10);
    MatrixXd Data(10,3);

    for(int i=0;i < 10;i++){
        for(int j=0;j<3;j++){
            if(j==1){
                Data(i,j) = 0;
            }
            if(j==0){
                Data(i,j) = float(i-4);
            }
        }
    }

    
    L << 1e-5, 1.5e-5, 1.7e-5, 1.0e-5, 1.44e-5, 1.033e-5, 1.1e-5, 1.71e-5, 1.2e-5, 1.17e-5;
    Data.col(2) = L;
    initial_model(10, elements, L);

    return 0;
}

