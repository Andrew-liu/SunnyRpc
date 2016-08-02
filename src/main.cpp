//
// Created by Andrew_liu on 16/7/26.
//
#include <iostream>
#include "echo.pb.h"

struct test {
    char m1;
    double m4;
    int m3;
};

int main() {
    std::cout << "Hello SunnyRpc" << std::endl;
    test t;
    std::cout << sizeof(t) << std::endl;
    return 0;
}
