#include <iostream>
#include <string>

#include "stringutils.h"
#include "divutils.h"

using namespace std::string_literals;

int main()
{
    //auto lines = readlines(DATADIR "small.txt"s);
    auto lines = readlines(DATADIR "input.txt"s);
    uint64_t count_2 = 0;
    uint64_t count_3 = 0;
    vector<char> seen {};
    for (const auto& line : lines) {
        bool counted_2 = false;
        bool counted_3 = false;
        std::cout << line << std::endl;
        seen.clear();
        for (const auto& letter : line) {
            if (contains(seen, letter)) {
                //std::cout << "already seen: " << letter << std::endl;
                continue;
            }
            auto lettercount = count(line, letter);
            switch (lettercount) {
            case 2:
                if (counted_2) break;
                std::cout << "repeated twice: " << letter << std::endl;
                seen.push_back(letter);
                count_2++;
                counted_2 = true;
                break;
            case 3:
                if (counted_3) break;
                std::cout << "repeated thrice: " << letter << std::endl;
                seen.push_back(letter);
                count_3++;
                counted_3 = true;
                break;
            }
        }
    }
    uint64_t checksum = count_2 * count_3;
    std::cout << checksum << std::endl;
    return 0;
}
