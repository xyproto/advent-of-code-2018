#include <iostream>
#include <string>

#include "divutils.h"
#include "stringutils.h"

using namespace std::string_literals;

// how many characters differs between two given strings?
// and which characters are then left as common characters?
auto common(std::string sa, std::string sb)
{
    auto counter = 0;
    size_t minlength = std::min(len(sa), len(sb));
    auto common = ""s;
    for (size_t i = 0; i < minlength; ++i) {
        if (sa[i] != sb[i]) {
            counter++;
        } else {
            common += sa[i];
        }
    }
    return pair<int,string>{counter,common};
}

int main()
{
    //auto lines = trimv(readlines(DATADIR "small.txt"s));
    auto lines = trimv(readlines(DATADIR "input.txt"s));

    for (const auto& word1 : lines) {
        for (const auto& word2 : lines) {
            if (word1 == word2) {
                continue;
            }
            auto [diffcount, commonletters] = common(word1, word2);
            if (diffcount == 1) {
                std::cout << commonletters << std::endl;
                return 0;
            }
        }
    }
    return 0;
}
