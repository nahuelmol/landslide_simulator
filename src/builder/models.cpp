
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <iostream>
#include "blocks.h"

#define G 6

float dimension(int i){
    //this should return 1/r^2
    float z = 5;
    float d = sqrt(std::pow(i,2) * std::pow(z,2));
    float result = 1.0/(std::pow(d,2));
    return result;
}

void least_squares(std::vector<float> L, std::vector<float> C) {
    //comparing
    std::vector<float> LSE;
    for(int i = 0; i < L.size(); i++){
        float diff = L[i] - C[i];
        float E = std::pow(diff, 2);
        LSE.push_back(E);
    }
}

float gen() {
    float n = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return n;
}

void initial_model(int n, std::string elements, std::vector<float> L) {
    if (elements == "polygons") {
        std::cout << "making Talwani approach" << std::endl;
    }
    //--@n blocks
    //--blocks's dimension will be a constant

    std::vector<float> calculated;
    std::vector<float> densities;
    for (int i = 0; i< n;i++){
        //Block BLOCK(i);
        float random = gen();
        densities.push_back(random);
        float effect = G * random * dimension(i);
        calculated.push_back(effect);
    }
    least_squares(L, calculated);
}


