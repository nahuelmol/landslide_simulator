
#include "Polygon.h"
#include "Stack.h"

Stack::Stack(int n, float delta) {
    this->n = n;
    this->delta = delta;
}

void Stack::add_polygon(Polygon P){
    (this->Polygons).push_back(P);
}

Polygon Stack::get_polygon(int i){
    (this->Polygons)[i];
}

