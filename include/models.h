
#ifndef MODELS_H
#define MODELS_H

#include <vector>
#include <iostream>

float dimension(int i);
float gen();
void initial_model(int n, std::string elements, std::vector<float> L);
void least_squares(std::vector<float> L, std::vector<float> C);

#endif //MODELS_H
