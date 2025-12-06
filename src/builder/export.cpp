
#include <fstream>
#include <Eigen/Dense>
#include <string>
#include <vector>

using Eigen::VectorXd;

void add_csv(VectorXd data) {
    std::ifstream infile("here.txt");
    std::vector<std::string> lines;
    std::string line;

    if (infile.is_open()){
        while (std::getline(infile, line)){
            lines.push_back(line);
        }
        infile.close();
    }
    for (int i = 0; i < int(data.size()); i++) {
        //lines[i].append(data[i]);
        lines[i] = lines[i] + "\t"+ std::to_string(data[i]);
    }
    std::ofstream outfile("here.txt");
    if(outfile.is_open()){
        for (const std::string& mline: lines) {
            outfile << mline << std::endl;
        }
        outfile.close();
    }
}

void make_csv(VectorXd data) {
    std::ofstream mifile("here.txt");
    for (auto each:data) {
        mifile << each << "\n";
    }
};
