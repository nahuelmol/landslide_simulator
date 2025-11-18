#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include "body.h"

using Eigen::MatrixXd;

Body::Body(float a, float b, float z_top) {
    this->a = a;
    this->b = b;
    this->z_top = z_top;
    this->longitude = a + z_top;
}

