
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
    std::vector<float> L = {1.3, 1.5, 1.7, 2.0, 2.44, 2.033, 3.1, 2.71};
    initial_model(8, elements, L);
    return 0;
}

