#include <cstdlib>
#include <iostream>
#include <string>

#include "numbers.h"

using namespace std::string_literals;

int main()
{
    auto n = Numbers(DATADIR "input.txt"s);
    std::cout << n.seen_twice() << std::endl;
    return EXIT_SUCCESS;
}
