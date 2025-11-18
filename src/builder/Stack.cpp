
#include "Polygon.h"
#include "Stack.h"

Stack::Stack(int n, float delta, float z_top) {
    this->n = n;
    this->delta = delta;
    this->z_top = z_top;
}

float Stack::add_polygon(int i){
    float z = (i * (this->delta)) + (this->z_top);
    this->polygons.push_back(z);
    return z;
}


Polygon Stack::get_polygon(int i){
    //return only polygon's z value
    return (this->polygons)[i];
}

