
#include <iostream>
#include "Polygon.h"
#include "Stack.h"

void build_stack(int n) {
    //--@n is amount of polygons
    int c = 4;
    float delta = 5.0;
    float z = 5.0;
    /*
    std::cout << "insert separation between polygons: " << std::endl;
    std::cin >> delta;
    std::cout << "insert amount of corners per polygon: " << std::endl;
    std::cin >> c;
    std::cout << "insert z: " << std::endl;
    std::cin >> z;
    */

    Stack ST(n, delta);
    Polygon P(c);
    //here is only one single z values, I must add the set of z values
    P.set_corners(float(z));
    P.set_phi();
    //ST.add_polygon(P);                      
    std::cout << "PHI:" << P.phi << std::endl;
}
