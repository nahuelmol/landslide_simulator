
#include <iostream>
#include <stdexcept>
#include <string>


void set_error(int code){
    char buffer[256];
}

struct MyCustomException : public std::runtime_error {
    using std::runtime_error::runtime_error; 
};

/*
void checkValue(int value) {
    if (value < 0) {
        // Throw an instance of the custom exception with a descriptive message
        throw MyCustomException("Value cannot be negative: " + std::to_string(value));
    }
    std::cout << "Value is valid: " << value << std::endl;
}
*/

