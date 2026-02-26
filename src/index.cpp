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
    std::string datapath = "data\\data.txt";
    std::ifstream infile(datapath);
    std::vector<std::string> lines;
    std::string line;

    int size = 0;
    if(infile.is_open()){
        while (std::getline(infile, line)){
            size++;
        }
        infile.close();
    }
    VectorXd L(size);
    MatrixXd data(size,4);
    for(int j=0; j<size; j++){
        data(j,0) = float(j);
        data(j,1) = 0;
        data(j,2) = 0;
        data(j,3) = 0;
    }

    int i = 0;
    std::vector<float> row;
    std::ifstream againfile(datapath);
    if(againfile.is_open()){
        while (std::getline(againfile, line)){
            std::stringstream ss(line);
            std::string item;
            while(std::getline(ss, item, '\t')){
                row.push_back(std::atof(item.c_str()));
            }
            VectorXd result = Eigen::Map<Eigen::VectorXf>(row.data(), row.size()).cast<double>();
            std::vector<float>().swap(row);
            data.row(i) = result;
            i++;
        }
        infile.close();
    }
    //make_csv(data.col(0));
    //add_csv(data.col(3));
    //implement();
    //plot("here.txt");

    Model* MODEL = new Model("polygons", data);
    MODEL->initial();

    return 0;
}



