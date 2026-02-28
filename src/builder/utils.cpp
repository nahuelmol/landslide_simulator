
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

void limpiar_ANSI() {
    printf("\033[2J"); // \033[2J: Borra toda la pantalla
    printf("\033[H");  // \033[H: Mueve el cursor a la esquina superior izquierda (1,1)
    fflush(stdout);   // Asegura que se envíe la salida inmediatamente
    std::cout << "\033[32m" << "Running." << "\033[0m" << std::endl;
}

float dimension(int i, int j){
    //this should return 1/r^2
    float xdelta = 1;
    float z = 5;
    float x = std::abs(i-j) * xdelta;
    float d = sqrt(std::pow(x,2) + std::pow(z,2));
    float result = 1.0/(std::pow(d,2));
    return result;
}

float gen() {
    srand(static_cast<unsigned int>(std::time(nullptr)));
    float n = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float result = n * 2.7;
    return result;
}
