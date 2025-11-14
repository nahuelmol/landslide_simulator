
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "models.h"

void navier_stokes_eq() {
    std::cout << "executing navier stokes eq"<< std::endl;
}

void euler_eq() {
    std::cout << "executing euler eq" << std::endl;
}

int main () {
    std::string elements = "polygon";
    std::vector<float> L = {1e-5, 1.5e-5, 1.7e-5, 1.0e-5, 1.44e-5, 1.033e-5, 1.1e-5, 1.71e-5, 1.2e-5, 1.17e-5};
    initial_model(8, elements, L);
    return 0;
}

