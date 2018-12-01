#pragma once

// Create a 2D array of (x, y), where (x, y) is the position to move to next.
// This makes it possible to repeatedly apply the vector field to a 2D array of numbers
// and make them move around, in order to solve Day 3.

#include "numbers.h"
#include "turtle.h"
#include <optional>
#include <sstream>
#include <vector>

using std::endl;
using std::nullopt;
using std::optional;
using std::string;
using std::stringstream;

using namespace std::literals;

class Vectorfield {

private:
    v3d _vf;

public:
    Vectorfield(
        size_t w, size_t h); // create an empty vectorfield, with all positions set to (0, 0)
    void spiral(); // create a field where all positions points in a spiral into the center
    bool set(size_t x, size_t y, p_t value); // set a value
    optional<p_t> get(size_t x, size_t y); // get a value
    string str();
    size_t width();
    size_t height();

    bool write(
        Turtle* t); // at the x,y from the turtle, write the turtle direction to the vector field
    bool write(int x, int y, pair<int, int> direction);

    optional<Vectorfield*> twirl(); // create a twirl from the center and out in spirals
    Vectorfield* reverse(); // reverse the direction of all the vectors

    optional<Numbers> apply(Numbers n); // apply the vectorfield to a 2d vector
};
