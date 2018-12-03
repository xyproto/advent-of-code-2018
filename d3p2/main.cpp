#include <cstdlib>
#include <iostream>

#include "patch.h"

using namespace std::string_literals;

int main(int argc, char** argv)
{
    // auto filename = DATADIR "simple.txt"s;
    auto filename = DATADIR "input.txt"s;

    if (argc > 1) {
        filename = argv[1];
    }

    Patch::Patch p;
    for (const auto& line : readlines(filename)) {
        p.add(line);
    }

    // p.draw();
    // std::cout << p.str() << std::endl;

    std::cout << "no overlap ID: " << p.no_overlap_ID() << std::endl;

    return EXIT_SUCCESS;
}
