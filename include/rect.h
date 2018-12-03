#pragma once

#include <string>

namespace Rect {

class Rect {
private:
    int _ID;
    int _x;
    int _y;
    int _w;
    int _h;

public:
    Rect(const int ID, const int x, const int y, const int w, const int h);

    bool hasPoint(int x, int y);

    auto max_w() -> int;
    auto max_h() -> int;
    auto ID() -> int;
    auto overlap(Rect other) -> bool;
    auto str() -> std::string;
};

}
