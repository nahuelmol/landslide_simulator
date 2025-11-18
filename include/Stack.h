#ifndef STACK_H
#define STACK_H

#include <vector>
#include "Polygon.h"

class Stack {
public:
    std::vector<float> polygons;
    int n;
    float delta;
    float z_top;

    Stack(int n, float delta, float z_top);
    float add_polygon(int i);
    Polygon get_polygon(int i);
};

#endif //STACK_H
