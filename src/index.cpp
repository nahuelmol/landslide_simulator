
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "models.h"
#include "fluid.h"
#include <Eigen/Dense>

using Eigen::VectorXd;
using Eigen::MatrixXd;

int main () {
    std::string elements = "polygons";
    VectorXd L(10);
    MatrixXd Data(10,4);

    for(int i=0;i < 10;i++){
        Data(i,0) = float(i-4);
        Data(i,1) = 0;
        Data(i,2) = 0;
    }

    
    L << 1e-5, 1.5e-5, 1.7e-5, 1.0e-5, 1.44e-5, 1.033e-5, 1.1e-5, 1.71e-5, 1.2e-5, 1.17e-5;
    Data.col(3) = L;
    //implement();
    initial_model(elements, Data);

    return 0;
}

