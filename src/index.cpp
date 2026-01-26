
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <Eigen/Dense>
#include <windows.h>
#include <winuser.h>
#include <wingdi.h>
#include <commctrl.h>
#include <stdio.h>

#include "resource.h"
#include "models.h"
#include "export.h"
#include "plotting.h"
#include "errors.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

int main() {
    VectorXd L(10);
    MatrixXd Data(10,4);

    for(int i=0;i < 10;i++){
        Data(i,0) = float(i);
        Data(i,1) = 0;
        Data(i,2) = 0;
    }

    L << 1e-5, 1.5e-5, 1.7e-5, 1.7e-5, 1.84e-5, 1.33e-5, 1.29e-5, 1.21e-5, 1.2e-5, 1.17e-5;
    Data.col(3) = L;
    //make_csv(Data.col(0));
    //add_csv(Data.col(3));
    //implement();
    //plot("here.txt");

    std::string elements = "polygons";
    initial_model(elements, Data) {
    return 0;
}



