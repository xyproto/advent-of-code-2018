#pragma once

#include "turtle.h"
#include <fstream>
#include <iterator>
#include <optional>
#include <sstream>
#include <vector>

using std::endl;
using std::ifstream;
using std::istream_iterator;
using std::istringstream;
using std::nullopt;
using std::optional;
using std::vector;

using v2d = vector<vector<int>>;

using p_t = pair<int, int>; // specifying movement, for instance (1, 0) for moving 1 to the right
using v3d = vector<vector<p_t>>;

class Numbers {

private:
    v2d _numbers;

public:
    Numbers(string fn); // read a file with a matrix of space and newline separated numbers (ints)
    Numbers(int w, int h); // initialize a certain size with zeros
    Numbers(int w); // initialize a certain size with zeros

    string str(); // return a string with a header and the contents of the 2d vector
    size_t width();
    size_t height();
    bool empty();
    vector<int> maxes(); // maximum number per row
    vector<int> mins(); // minimum number per row
    vector<int> divs(); // result of dividing the numbers that can be divided per row

    int64_t sum(); // add all the numbers together

    // seen_twice adds all the numbers together repeatedly,
    // until the intermediate result has been seen twice. Returns that element.
    int64_t seen_twice();

    bool set(size_t x, size_t y, int value); // returns true if x and y were within range
    optional<int> get(size_t x, size_t y); // returns a value, if possible

    int center(); // the center value

    optional<p_t> find(int value); // finds the position of a value
    optional<int> manhattan(
        int value); // finds the manhattan distance from the value, if found, to the center

    optional<Numbers*> twirl(); // add a twirl

    int sum_surrounding(size_t x, size_t y);

    optional<Numbers*>
    twirl_sum_surrounding(); // add a twirl that sums the surrounding numbers as it goes

    optional<int> twirl_sum_surrounding_quit_after(
        int q); // Return the following number after the one given

    bool write(Turtle* t, int value); // write a value at the turtle position
};

int next_twirl_sum_number(int size, int value);
