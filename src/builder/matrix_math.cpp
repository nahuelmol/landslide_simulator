
#include <vector>
#include <iostream>

std::vector<std::vector<float>> transpose(std::vector<std::vector<float>> D) {
    float aux;
    int cols = D[0].size();
    int rows = D.size();

    for(int i=0;i<cols;i++){
        for(int j; j< rows;j++){
            aux = D[i][j];
            D[i][j] = D[j][i];
            D[j][i] = aux;
        }
    }
    return D;
}
