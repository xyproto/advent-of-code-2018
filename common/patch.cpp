#include <vector>

#include "patch.h"
#include "rect.h"

using std::vector;

namespace Patch {

void Patch::add(std::string ID_pos_size)
{
    // std::cout << "Adding " << ID_pos_size << " to patch." << std::endl;

    // Parse the given string
    auto [hash_ID, pos_size] = twofields(ID_pos_size, "@");
    auto [_, ID] = twofields(hash_ID, "#");
    auto [pos, size] = twofields(pos_size, ":");
    auto [x, y] = twofields(pos, ",");
    auto [w, h] = twofields(size, "x");

    // Add to patch
    auto r = Rect::Rect(mustInt(ID), mustInt(x), mustInt(y), mustInt(w), mustInt(h));
    _rects.push_back(r);
}

auto Patch::count(int x, int y) -> int
{
    auto counter { 0 };
    for (auto& e : _rects) {
        if (e.hasPoint(x, y)) {
            counter++;
        }
    }
    return counter;
}

auto Patch::count(pair<int, int> pos) -> int
{
    // Call the other method
    return count(pos.first, pos.second);
}

auto Patch::max_w() -> int
{
    auto x { 0 };
    for (auto& e : _rects) {
        if (e.max_w() > x) {
            x = e.max_w();
        }
    }
    return x;
}

auto Patch::max_h() -> int
{
    auto y { 0 };
    for (auto& e : _rects) {
        if (e.max_h() > y) {
            y = e.max_h();
        }
    }
    return y;
}

auto Patch::overlapcount() -> int
{
    auto counter { 0 };
    for (int y = 0; y < this->max_h(); ++y) {
        for (int x = 0; x < this->max_w(); ++x) {
            if (this->count(x, y) >= 2) {
                counter++;
            }
        }
    }
    return counter;
}

void Patch::draw()
{
    for (int y = 0; y < this->max_h(); ++y) {
        for (int x = 0; x < this->max_w(); ++x) {
            int count = this->count(x, y);
            switch (count) {
            case 0:
                std::cout << " ";
                break;
            case 1:
                std::cout << "1";
                break;
            default:
                std::cout << "M";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Returns the first rectangle ID with no overlaps with any other rectangle, or -1 if not found.
int Patch::no_overlap_ID()
{
    for (auto& r1 : this->_rects) {
        // std::cout << "---" << std::endl;
        bool overlaps = false;
        for (auto& r2 : this->_rects) {
            if (r1.ID() == r2.ID()) {
                // std::cout << "SAME!" << std::endl;
                continue;
            }
            if (r1.overlap(r2)) {
                // std::cout << r1.str() << " overlaps " << r2.str() << std::endl;
                overlaps = true;
                break;
            } else {
                // std::cout << r1.str() << " does not overlap " << r2.str() << std::endl;
            }
        }
        if (!overlaps) {
            return r1.ID();
        }
    }
    return -1;
}

// Output as a string
std::string Patch::str()
{
    std::stringstream ss;
    ss << "List of rects:" << std::endl;
    for (auto& e : _rects) {
        ss << e.str() << std::endl;
    }
    return ss.str();
}

}
