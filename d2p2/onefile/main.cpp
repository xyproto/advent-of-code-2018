/*
 * Advent of Code 2018, day 2 part 2.
 * C++17. All in one source file.
 * Written by Alexander F. Rødseth, CC0 licensed.
 *
 * Compilation with clang: clang++ -Ofast -std=c++17 main.cpp -o main
 * Compilation with gcc:       g++ -Ofast -std=c++17 main.cpp -o main
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std::string_literals;

// Get the length of variables with .length(), inspired by Python and Go
template <class T> inline auto len(const T& s) { return s.length(); }

// Read in all the lines in a text file. Quick and dirty, no particular error
// checking. May log an error to stderr and return an empty vector if the file
// does not open.
auto readlines(const std::string& filename) -> const std::vector<std::string>
{
    std::vector<std::string> lines {};
    std::string line;
    std::ifstream infile { filename, std::ifstream::in };
    if (infile.is_open()) {
        while (getline(infile, line)) {
            std::istringstream is { line };
            lines.push_back(is.str());
        }
    } else {
        std::cerr << "Could not open "s << filename << std::endl;
    }
    return lines;
}

// How many characters differs between two given strings?
// And which characters are then left as common characters?
auto common(std::string sa, std::string sb)
{
    size_t counter = 0;
    auto common = ""s;
    size_t minlength = std::min(len(sa), len(sb));
    for (size_t i = 0; i < minlength; ++i) {
        if (sa[i] != sb[i]) {
            counter++;
        } else {
            common += sa[i];
        }
    }
    return std::pair<int, std::string> { counter, common };
}

auto main() -> int
{
    auto lines = readlines("input.txt"s);
    for (const auto& word1 : lines) {
        for (const auto& word2 : lines) {
            if (word1 == word2) {
                continue;
            }
            const auto [diffcount, commonletters] = common(word1, word2);
            if (diffcount == 1) {
                std::cout << commonletters << std::endl;
                return 0;
            }
        }
    }
    return 0;
}
