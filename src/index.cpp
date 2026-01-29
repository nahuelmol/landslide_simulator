#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <Eigen/Dense>
#include <windows.h>
#include <winuser.h>
#include <wingdi.h>
#include <commctrl.h>

#include "resource.h"
#include "models.h"
#include "export.h"
#include "plotting.h"
#include "errors.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using Eigen::Map;
using Eigen::VectorXf;

int main() {
    VectorXd L(10);
    MatrixXd Data(10,4);

    for(int i=0;i < 10;i++){
        Data(i,0) = float(i);
        Data(i,1) = 0;
        Data(i,2) = 0;
        Data(i,3) = 0;
    }

    std::string datapath = "data\\data.txt";
    std::ifstream infile(datapath);
    std::vector<std::string> lines;
    std::string line;
    std::vector<float> row;

    int i = 0;
    if(infile.is_open()){
        while (std::getline(infile, line)){
            std::stringstream ss(line);
            std::string item;
            while(std::getline(ss, item, '\t')){
                row.push_back(std::atof(item.c_str()));
            }
            VectorXd result = Eigen::Map<Eigen::VectorXf>(row.data(), row.size()).cast<double>();
            std::vector<float>().swap(row);
            Data.row(i) = result;
            i++;
        }
        infile.close();
    }
    //make_csv(Data.col(0));
    //add_csv(Data.col(3));
    //implement();
    //plot("here.txt");

    std::string elements = "polygons";
    initial_model(elements, Data);
    return 0;
}



