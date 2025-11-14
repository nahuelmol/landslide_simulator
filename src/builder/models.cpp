
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "blocks.h"

const double G = 6.67430e-11;

float dimension(int i, int j){
    //this should return 1/r^2
    float xdelta = 1;
    float z = 5;
    float x = std::abs(i-j) * xdelta;
    float d = sqrt(std::pow(x,2) + std::pow(z,2));
    float result = 1.0/(std::pow(d,2));
    return result;
}

void least_squares(std::vector<float> L, std::vector<float> C, std::vector<std::vector<float>> dims, std::vector<float> dens) {
    //comparing
    std::vector<float> LSE;
    for(int i = 0; i < L.size(); i++){
        float diff = L[i] - C[i];
        float E2 = std::pow(diff, 2);
        LSE.push_back(E2);
    }
    for(float each: LSE){
        std::cout << "LSE -> " << each << std::endl;
    }
}

float gen() {
    srand(static_cast<unsigned int>(time(nullptr)));
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
    std::vector<float> row; 
    std::vector<std::vector<float>> dimensions;

    for (int j = 0; j<n; j++){
        float random = gen();
        densities.push_back(random);
    }
    float aux = 0.0;
    for (int i = 0; i< n;i++){
        //Block BLOCK(i); for object oriented
        for(int j = 0; j < n; j++) {
            float dim = dimension(i,j);
            row.push_back(dim);
            float effect = G * densities[j] * dim;
            aux = effect + aux;
        }
        dimensions.push_back(row);
        row.clear();
        calculated.push_back(aux);
        aux = 0.0;
    }
    for(float each:calculated){
        std::cout << "effect ->" << each << std::endl;
    }
    least_squares(L, calculated, dimensiones, densities);
}


