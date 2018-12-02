#include <iostream>
#include <string>

#include "divutils.h"
#include "stringutils.h"

using namespace std::string_literals;

// diff between two strings, measured in average-ish diff per character
int diff(std::string sa, std::string sb)
{
    uint64_t sum { 0 };
    for (const auto& a : sa) {
        for (const auto& b : sb) {
            sum += abs(static_cast<int>(a) - static_cast<int>(b));
        }
    }
    sum /= (len(sa) + len(sb));
    return static_cast<int>(sum);
}

int main()
{
    auto lines = readlines(DATADIR "small.txt"s);
    // auto lines = readlines(DATADIR "input.txt"s);
    
    for (int i=0; i < len(lines)-1; ++i) {
        std::cout << lines[i] << std::endl;
        std::cout << "diff " << diff(lines[i], lines[i+1]) << std::endl;
        std::cout << lines[i+1] << std::endl;
        std::cout << "---" << std::endl;
    }

    for (const auto& line : lines) {
    }

    return 0;
}
