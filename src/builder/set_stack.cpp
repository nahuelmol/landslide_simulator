
#include <iostream>
#include "Polygon.h"
#include "Stack.h"

void build_stack(int n) {
    //--@n is amount of polygons
    int c;
    float delta;
    std::cout << "insert separation between polygons" << std::endl;
    std::cin >> delta;
    std::cout << "insert amount of corners per polygon" << std::endl;
    std::cin >> c;

    Stack ST(n, delta);
    Polygon P(c);
    P.set_corners();
    ST.add_polygon(P);                      
}
