
#include <iostream>
#include "Polygon.h"
#include "Stack.h"
#include "Body.h"

#include "Eigen/Dense"

using Eigen::MatrixXd;

Stack* build_stack(int n, MatrixXd Data) {
    //--@n is amount of polygons
    int c = 4;

    int L = Data.rows();
    Body* BODY = new Body(10.0, 6.0, 2.5f);
    float delta = (BODY->longitude)/(n+1);
    Stack* ST = new Stack(n, L, delta, 2.5);

    for(int j=0; j<L;j++){
        for(int i=0;i<n;i++){
            Polygon* P = new Polygon(c);
            ST->add_polygon(P, i);
            P->set_corners(BODY);
            P->set_phi(Data, j);
            float z = Data(j,2);
            ST->add_phi(P->phi, i, j, z, P->z);
        }
    }
    return ST;
}
