
#ifndef POLYGON_H
#define POLYGON_H

#include <Eigen/Dense>

using Eigen::MatrixXd;

class Polygon {
public:
    float z = 0;
    int ncorners = 0;
    float phi = 0.0;
    MatrixXd corners;

    Polygon(int c);
    void set_corners(float z);
    void set_phi();
    MatrixXd get_corners();
};

#endif //POLYGON_H
