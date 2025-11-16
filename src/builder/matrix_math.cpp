
#include <vector>
#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;

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

void inverse(MatrixXd D){
    MatrixXd D_I = D.inverse();
    std::cout << "D_I:\n" << D_I << std::endl;
    bool is_simec = D.isApprox(D.transpose());
    if(is_simec) {
        std::cout << "is simectric" << std::endl;
    }
}

