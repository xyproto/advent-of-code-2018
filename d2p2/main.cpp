#include <iostream>
#include <string>

#include "stringutils.h"
#include "divutils.h"

using namespace std::string_literals;

vector<int> string2nums(const std::string& s) {
    vector<int> nums {};
    for (const auto& letter : s) {
        nums.push_back(static_cast<int>(letter));
    }
    return nums;
}

// diff between two strings
int diff(std::string a, std::stringb) {
    for (const auto& letter_a : a) {
        // 
    }
}

int main()
{
    auto lines = readlines(DATADIR "small.txt"s);
    //auto lines = readlines(DATADIR "input.txt"s);

    for (const auto& line : lines) {
        std::cout << line << std::endl;
        std::cout << string2nums(line) << std::endl;
    }

    return 0;
}
