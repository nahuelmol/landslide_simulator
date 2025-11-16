
#ifndef POLYGON_H
#define POLYGON_H

#include <Eigen/Dense>

using Eigen::MatrixXd;

class Polygon {
public:
    int z = 0;
    int ncorners = 0;
    MatrixXd corners;

    Polygon(int c);
    void set_corners();
    MatrixXd get_corners();
};

#endif //POLYGON_H
