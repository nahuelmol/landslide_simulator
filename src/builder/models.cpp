
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "blocks.h"
#include "matrix_math.h"

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
    float BIAS_SSE = 0.5;
    float SSE = 0.0;
    std::vector<float> modified_C;
    std::vector<float> diffs;
    for(int i = 0; i < int(L.size()); i++){
        float diff = L[i] - C[i];
        diffs.push_back(diff);
        float E2 = std::pow(diff, 2);
        SSE = SSE + E2;
        LSE.push_back(E2);
    }

    if(SSE < BIAS_SSE) {
        std::cout << "SSE:" << SSE << std::endl;
        std::cout << "BIAS_SSE:" << BIAS_SSE << std::endl;
    }

    for(int i=0; i<int(L.size()); i++){
        modified_C.push_back(C[i] - (diffs[i] * 0.01));
    }
    
    for(int i=0; i<int(L.size()); i++){
        std::cout << "\nC" << i <<":"<< C[i] << std::endl;
        std::cout << "mod_C" << i <<":"<< modified_C[i] << std::endl;
    }

    std::cout << "D" << std::endl; 
    for(int i=0;i<int(dims[0].size());i++){
        for (int j=0;j<int(dims.size());j++){
            std::cout << dims[i][j] << " ";
        }
        std::cout << "\n" << std::endl;
    }
    std::vector<std::vector<float>> DT = transpose(dims);
    std::cout << "DT" << std::endl; 
    for(int i=0;i<int(DT[0].size());i++){
        for (int j=0; j<int(DT.size()) ;j++){
            std::cout << DT[i][j] << " ";
        }
        std::cout << "\n" << std::endl;
    }
}

float gen() {
    srand(static_cast<unsigned int>(time(nullptr)));
    float n = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float result = n * 2.7;
    return result;
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
        float sigma = gen();
        densities.push_back(sigma);
    }
    float aux = 0.0;
    for (int i = 0; i< int(L.size());i++){
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
    std::cout << "\n\n" << std::endl;
    least_squares(L, calculated, dimensions, densities);
}


