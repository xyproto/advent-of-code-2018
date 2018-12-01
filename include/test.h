#pragma once

#include <iostream>
#include <cstdlib>

using namespace std::literals;

template<typename T>
void equal(T a, T b) {
    if (a == b) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
        exit(EXIT_FAILURE);
    }
}
