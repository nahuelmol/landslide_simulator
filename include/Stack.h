#ifndef STACK_H
#define STACK_H

#include <vector>
#include "Polygon.h"
#include <Eigen/Dense>

using Eigen::MatrixXd;

class Stack {
public:
    std::vector<float> locations;
    std::vector<Polygon*> polygons;
    int n;
    float delta;
    float z_top;
    MatrixXd PHI;

    Stack(int n, float delta, float z_top);
    void add_polygon(Polygon* P,int i);
    Polygon get_polygon(int i);
    void add_phi(float phi_m, int i);
};

#endif //STACK_H
