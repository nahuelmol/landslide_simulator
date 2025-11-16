#ifndef STACK_H
#define STACK_H

#include <vector>
#include "Polygon.h"

class Stack {
public:
    std::vector<Polygon> Polygons;
    int n;
    float delta;

    Stack(int n, float delta);
    void add_polygon(Polygon P);
    Polygon get_polygon(int i);
};

#endif //STACK_H
