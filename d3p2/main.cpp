#include <cstdlib>
#include <iostream>

#include "stringutils.h"

using namespace std::string_literals;

class Rect {
private:
    int _ID;
    int _x;
    int _y;
    int _w;
    int _h;

public:
    Rect(const int ID, const int x, const int y, const int w, const int h);

    std::string str();
    bool has(int x, int y);

    int max_w();
    int max_h();

    int ID();

    bool overlap(Rect other);
};

Rect::Rect(const int ID, const int x, const int y, const int w, const int h)
{
    _x = x;
    _y = y;
    _w = w;
    _h = h;
    _ID = ID;
}

auto Rect::str() -> std::string
{
    std::stringstream ss;
    ss << "Rect #" << _ID << " (" << _x << ", " << _y << "), " << _w << "x" << _h;
    return ss.str();
}

inline auto Rect::has(int x, int y) -> bool
{
    return (x >= _x) && (y >= _y) && (x < (_x + _w)) && (y < (_y + _h));
}

// Check if this rectangle overlaps with another rectangle, or not
inline auto Rect::overlap(Rect other) -> bool
{
    // left side of the other rectangle is to the right of this one?
    bool left = other._x > (_x + _w);

    // right side of the other rectangle is to the left of this one?
    bool right = (other._x + other._w) < _x;

    // top side of the other rectangle is below this one?
    bool top = other._y > (_y + _h);

    // bottom side of the other rectange is above this one?
    bool bot = (other._y + other._h) < _y;

    // Either to the left or right or above or below, then there is no overlap.
    return !(left || right || top || bot);
}

inline auto Rect::max_w() -> int { return _x + _w; }

inline auto Rect::max_h() -> int { return _y + _h; }

inline auto Rect::ID() -> int { return _ID; }

class Patch {
private:
    vector<Rect> _rects;

public:
    // Add a patch
    void add(std::string ID_pos_size);

    // Number of rectangles that has this coordinate
    int count(int x, int y);
    int count(pair<int, int> pos);

    // Draw ASCII graphics
    void draw();

    // Output as a string
    std::string str()
    {
        std::stringstream ss;
        ss << "List of rects:" << std::endl;
        for (auto& e : _rects) {
            ss << e.str() << std::endl;
        }
        return ss.str();
    }

    int max_w();
    int max_h();

    int overlapcount();

    int no_overlap_ID();
};

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
    auto r = Rect(mustInt(ID), mustInt(x), mustInt(y), mustInt(w), mustInt(h));
    _rects.push_back(r);
}

inline auto Patch::count(int x, int y) -> int
{
    auto counter { 0 };
    for (auto& e : _rects) {
        if (e.has(x, y)) {
            counter++;
        }
    }
    return counter;
}

inline auto Patch::count(pair<int, int> pos) -> int
{
    // Call the other method
    return count(pos.first, pos.second);
}

inline auto Patch::max_w() -> int
{
    auto x { 0 };
    for (auto& e : _rects) {
        if (e.max_w() > x) {
            x = e.max_w();
        }
    }
    return x;
}

inline auto Patch::max_h() -> int
{
    auto y { 0 };
    for (auto& e : _rects) {
        if (e.max_h() > y) {
            y = e.max_h();
        }
    }
    return y;
}

inline auto Patch::overlapcount() -> int
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

int main(int argc, char** argv)
{
    // auto filename = DATADIR "simple.txt"s;
    auto filename = DATADIR "input.txt"s;

    Patch p;
    for (const auto& line : readlines(filename)) {
        p.add(line);
    }

    // p.draw();
    // std::cout << p.str() << std::endl;

    std::cout << "no overlap ID: " << p.no_overlap_ID() << std::endl;

    return EXIT_SUCCESS;
}
