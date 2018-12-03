#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "stringutils.h"
#include "test.h"

using namespace std::string_literals;

class Rect {
private:
    int _x;
    int _y;
    int _w;
    int _h;

public:
    Rect(int x, int y, int w, int h);

    std::string str();
    bool has(int x, int y);

    int max_w();
    int max_h();
};

Rect::Rect(int x, int y, int w, int h)
{
    _x = x;
    _y = y;
    _w = w;
    _h = h;
}

auto Rect::str() -> std::string
{
    std::stringstream ss;
    ss << "Rect (" << _x << ", " << _y << "), " << _w << "x" << _h;
    return ss.str();
}

inline auto Rect::has(int x, int y) -> bool
{
    return (x >= _x) && (y >= _y) && (x < (_x + _w)) && (y < (_y + _h));
}

int Rect::max_w() { return _x + _w; }

int Rect::max_h() { return _y + _h; }

class Patch {
private:
    vector<Rect> _rects;

public:
    // Add a patch
    void add(std::string id_pos_size);

    // Number of rectangles that has this coordinate
    int count(int x, int y);

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
};

void Patch::add(std::string id_pos_size)
{
    // std::cout << "Adding " << id_pos_size << " to patch." << std::endl;

    // Parse the given string
    auto [hash_id, pos_size] = twofields(id_pos_size, "@");
    auto [_, id] = twofields(hash_id, "#");
    auto [pos, size] = twofields(pos_size, ":");
    auto [x, y] = twofields(pos, ",");
    auto [w, h] = twofields(size, "x");

    // Add to patch
    auto r = Rect(mustInt(x), mustInt(y), mustInt(w), mustInt(h));
    _rects.push_back(r);
}

auto Patch::count(int x, int y) -> int
{
    auto counter { 0 };
    for (auto& e : _rects) {
        if (e.has(x, y)) {
            counter++;
        }
    }
    return counter;
}

int Patch::max_w()
{
    auto x { 0 };
    for (auto& e : _rects) {
        if (e.max_w() > x) {
            x = e.max_w();
        }
    }
    return x;
}

int Patch::max_h()
{
    auto y { 0 };
    for (auto& e : _rects) {
        if (e.max_h() > y) {
            y = e.max_h();
        }
    }
    return y;
}

int Patch::overlapcount()
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

int main(int argc, char** argv)
{
    // auto filename = DATADIR "simple.txt"s;
    auto filename = DATADIR "input.txt"s;

    Patch p;
    for (const auto& line : readlines(filename)) {
        p.add(line);
    }

    // p.draw();

    std::cout << p.str() << std::endl;

    // std::cout << "TEST 1: ";
    // equal(p.count(0,0), 0);

    // std::cout << "TEST 2: ";
    // equal(p.count(1,1), 0);

    // std::cout << "TEST 3: ";
    // equal(p.count(3,3), 2);

    // std::cout << "TEST 4: ";
    // equal(p.count(5,5), 1);

    // std::cout << "TEST 5: ";
    // equal(p.count(6,6), 1);

    // std::cout << "TEST 6: ";
    // equal(p.count(7,7), 0);

    // std::cout << "TEST 7: ";
    // equal(p.count(7,1), 0);

    std::cout << std::endl;

    std::cout << "overlapcount: " << p.overlapcount() << std::endl;

    return EXIT_SUCCESS;
}
