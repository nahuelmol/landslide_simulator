
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
    std::vector<float> L = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    initial_model(8, elements, L);
    return 0;
}

