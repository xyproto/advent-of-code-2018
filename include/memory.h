#pragma once

#include "util.h"
#include <cmath>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using std::cout;
using std::endl;
using std::nullopt;
using std::optional;
using std::pair;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::vector;

using index_t = size_t;

class Memory {

private:
    vector<int> _memory;

public:
    Memory(vector<int> memory);
    Memory(size_t size);

    string str();

    optional<pair<index_t, int>> largest();

    // Used together with must(T, U) to return a "not found" value
    pair<index_t, int> NotFound = pair<index_t, int> { 0, -1 };

    // Return the largest value, or -1 if not found
    int must_largest_value();

    // Return the position with the largest value or 0 if not found
    index_t must_largest_position();

    // Redistribute the largest one on the others, return the number of redistributions
    unsigned redistribute();

    // Return the contents
    vector<int> get();

    // Return a size_t representing the vector<int>
    size_t hash();

    // Return the number of iterations of redistribution until the result has been seen before
    optional<unsigned> redistribution_number(unsigned max_iterations);

    // Same as redistribution_number, but without any safeguards (!)
    unsigned must_redistribution_number();

    // Find the number of redistributions, not only redistribution cycles
    unsigned redistributions_cached();

    // Find the number of iterations between the first re-encounter and the next re-encounter
    unsigned re_encounter_iterations();
};
