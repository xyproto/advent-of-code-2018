#pragma once

#include "rect.h"
#include "stringutils.h"

#include <sstream>
#include <utility>
#include <vector>

using std::pair;
using std::string;
using std::stringstream;
using std::vector;

namespace Patch {

using p_t = pair<int, int>;

class Patch {
private:
    vector<Rect::Rect> _rects;

public:
    // Add a patch
    void add(std::string ID_pos_size);

    // Number of rectangles that has this coordinate
    auto count(int x, int y) -> int;
    auto count(p_t pos) -> int;

    // Draw ASCII graphics
    void draw();

    auto max_w() -> int;
    auto max_h() -> int;
    auto overlapcount() -> int;
    auto no_overlap_ID() -> int;

    auto str() -> std::string;
};

}
