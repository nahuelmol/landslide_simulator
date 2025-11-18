
#include <iostream>
#include "Polygon.h"
#include "Stack.h"
#include "Body.h"

void build_stack(int n) {
    //--@n is amount of polygons
    int c = 4;
    /*
    std::cout << "insert separation between polygons: " << std::endl;
    std::cin >> delta;
    std::cout << "insert amount of corners per polygon: " << std::endl;
    std::cin >> c;
    std::cout << "insert z: " << std::endl;
    std::cin >> z;
    */

    std::cout << "hellow" << std::endl;
    Body* BODY = new Body(10.0, 6.0, -2.5f);
    float delta = (BODY->longitude)/(n+2);
    Stack* ST = new Stack(n, delta, -2.5);
    for(int i;i<n;i++){
        Polygon* P = new Polygon(c);
        float z = ST->add_polygon(i);
        P->z = z;
        P->set_corners(BODY);
        P->set_phi();
        std::cout << "PHI:" << P->phi << std::endl;
    }
    //here is only one single z values, I must add the set of z values
}
