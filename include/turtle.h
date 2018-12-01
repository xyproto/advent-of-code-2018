#pragma once 

#include <math.h>
#include <string>
#include <sstream>

using std::pair;
using std::string;
using std::stringstream;

using p_t = pair<int, int>;

class Turtle {
private:

  int _x;
  int _y;
  p_t _direction;

public:

  // No bounds check, it's not the Turtle's job

  Turtle(int x, int y, int direction_x, int direction_y);
  Turtle(pair<int, int> pos, pair<int, int> direction);
  void set_direction(p_t v);
  void set_direction(int x, int y);
  p_t get_direction();
  void forward();
  void left();
  int x();
  int y();
  string str();

  //bool write(Vectorfield* vf);
  //bool move_turn_write(Vectorfield* vf, bool turn_left_after_moving);
  void move_turn(bool turn_left_after_moving);
};
