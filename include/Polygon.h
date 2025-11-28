
#ifndef POLYGON_H
#define POLYGON_H

#include <Eigen/Dense>
#include "body.h"

using Eigen::MatrixXd;

class Polygon {
public:
    float z = 0;
    int ncorners = 0;
    float phi = 0.0;
    MatrixXd corners;

    Polygon(int c);
    void set_corners(Body* BODY);
    void set_phi(MatrixXd Data);
    MatrixXd get_corners();
};

#endif //POLYGON_H
