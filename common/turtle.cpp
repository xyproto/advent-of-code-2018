#include "turtle.h"

Turtle::Turtle(int x, int y, int direction_x, int direction_y) {
    _x = x;
    _y = y;
    _direction = p_t {direction_x, direction_y};
}

Turtle::Turtle(pair<int, int> pos, pair<int, int> direction) {
    _x = pos.first;
    _y = pos.second;
    _direction = direction;
}

void Turtle::set_direction(p_t v) {
    _direction = v;
}

void Turtle::set_direction(int x, int y) {
    _direction.first = x;
    _direction.second = y;
}

p_t Turtle::get_direction() {
    return _direction;
}

void Turtle::forward() {
    _x += _direction.first;
    _y += _direction.second;
}

// turn left
void Turtle::left() {
    double d_x = static_cast<double>(_direction.first);
    double d_y = static_cast<double>(_direction.second);
    const double angle_offset = -(M_PI/2.0); // 90 degrees left, in radians
    double length = sqrt((d_x * d_x) + (d_y * d_y));
    double normalized_x = d_x / length;
    double normalized_y = d_y / length;
    double current_angle = atan2(normalized_y, normalized_x); // the current angle
    double angle = current_angle + angle_offset; // the new angle
    double new_x = length * cos(angle);
    double new_y = length * sin(angle);
    _direction.first = static_cast<int>(round(new_x));
    _direction.second = static_cast<int>(round(new_y));
}

void Turtle::move_turn(bool turn_left_after_moving) {
    this->forward();
    if (turn_left_after_moving) {
        this->left();
    }
}

int Turtle::x() {
    return _x;
}

int Turtle::y() {
    return _y;
}

string Turtle::str() {
    stringstream s;
    s << "Turtle at (" << _x << ", " << _y << ") heading (" << _direction.first << ", " << _direction.second << ")";
    return s.str();
}
