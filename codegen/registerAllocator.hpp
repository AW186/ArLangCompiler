#ifndef REGISTER_HPP
#define REGISTER_HPP

#include <iostream>

using namespace std;

class RegisterAllocator {
    string getRegister();
    void freeRegister(string register);
}


#endif