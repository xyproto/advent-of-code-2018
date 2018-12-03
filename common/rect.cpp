#include <sstream>

#include "rect.h"

namespace Rect {

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

// Check if this rectangle overlaps with another rectangle, or not
auto Rect::overlap(Rect other) -> bool
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

auto Rect::max_w() -> int { return _x + _w; }

auto Rect::max_h() -> int { return _y + _h; }

auto Rect::ID() -> int { return _ID; }

bool Rect::hasPoint(int x, int y)
{
    return (x >= _x) && (y >= _y) && (x < (_x + _w)) && (y < (_y + _h));
}

}
