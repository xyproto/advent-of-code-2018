#include "numbers.h"
#include "divutils.h"

using std::string;
using std::vector;

Numbers::Numbers(string fn)
{
    string line;
    ifstream infile { fn, ifstream::in };
    if (infile.is_open()) {
        while (getline(infile, line)) {
            istringstream is { line };
            _numbers.push_back(vector<int>(istream_iterator<int>(is), istream_iterator<int>()));
        }
    }
}

// Initialize a new 2d vector with 0
Numbers::Numbers(int w, int h)
{
    vector<int> row;
    for (int i = 0; i < w; ++i) {
        row.push_back(0);
    }
    for (int i = 0; i < h; ++i) {
        _numbers.push_back(row);
    }
}

Numbers::Numbers(int w)
{
    vector<int> row;
    for (int i = 0; i < w; ++i) {
        row.push_back(0);
    }
    for (int i = 0; i < w; ++i) {
        _numbers.push_back(row);
    }
}

string Numbers::str()
{
    stringstream s;
    s << this->width() << "x" << this->height() << " vector of ints: " << endl;
    for (const vector<int>& row : _numbers) {
        auto counter = row.size() - 1;
        for (const int& i : row) {
            s << i;
            if (counter-- > 0) { // "go to" operator ;)
                s << ", ";
            }
        }
        s << endl;
    }
    return s.str();
}

bool Numbers::empty() { return _numbers.size() == 0; }

size_t Numbers::width()
{
    if (this->empty()) {
        return 0;
    }
    return _numbers[0].size();
}

size_t Numbers::height()
{
    if (this->empty()) {
        return 0;
    }
    return _numbers.size();
}

vector<int> Numbers::maxes()
{
    vector<int> maxes;
    if (this->empty()) {
        return maxes;
    }
    for (const vector<int>& v : _numbers) {
        int max = v[0];
        for (const int& i : v) {
            if (i > max) {
                max = i;
            }
        }
        maxes.push_back(max);
    }
    return maxes;
}

vector<int> Numbers::mins()
{
    vector<int> mins;
    if (this->empty()) {
        return mins;
    }
    for (const vector<int>& v : _numbers) {
        int min = v[0];
        for (const int& i : v) {
            if (i < min) {
                min = i;
            }
        }
        mins.push_back(min);
    }
    return mins;
}

vector<int> Numbers::divs()
{
    vector<int> divs;
    if (this->empty()) {
        return divs;
    }
    for (const vector<int>& v : _numbers) {
        // Try all combinations of numbers per row
        for (const int& a : v) {
            for (const int& b : v) {
                if (a == b) {
                    continue;
                }
                if (a % b == 0) {
                    divs.push_back(a / b);
                    break;
                }
            }
        }
    }
    return divs;
}

// seen_twice adds numbers together repeatedly until the intermediate
// result has been seen twice. Warning: enters a potentially endless loop!
int64_t Numbers::seen_twice()
{
    int64_t x = 0;
    vector<int64_t> seen {};
    if (this->empty()) {
        return x;
    }
    for (;;) {
        for (const vector<int>& v : _numbers) {
            for (const int& i : v) {
                x += static_cast<uint64_t>(i);
                if (!contains(seen, x)) {
                    // std::cout << x << " has never been seen before!" << std::endl;
                    seen.push_back(x);
                } else {
                    // std::cout << x << " has already been seen!" << std::endl;
                    return x;
                }
            }
        }
    }
}

// sum adds together all numbers, positive or negative
int64_t Numbers::sum()
{
    int64_t s = 0;
    if (this->empty()) {
        return s;
    }
    for (const vector<int>& v : _numbers) {
        for (const int& i : v) {
            s += static_cast<uint64_t>(i);
        }
    }
    return s;
}

bool Numbers::set(size_t x, size_t y, int value)
{
    if (_numbers.size() <= y) {
        return false;
    }
    if (_numbers[y].size() <= x) {
        return false;
    }
    _numbers[y][x] = value;
    return true;
}

optional<int> Numbers::get(size_t x, size_t y)
{
    if (_numbers.size() <= y) {
        return nullopt;
    }
    if (_numbers[y].size() <= x) {
        return nullopt;
    }
    return optional { _numbers[y][x] };
}

// the center value, or -1
int Numbers::center()
{
    auto w2 = this->width() / 2;
    auto h2 = this->height() / 2;
    auto maybeInt = this->get(w2, h2);
    if (maybeInt) {
        return *maybeInt;
    }
    return -1;
}

// finds the position of a value
optional<p_t> Numbers::find(int value)
{
    if (this->empty()) {
        return nullopt;
    }
    for (size_t y = 0; y < this->height(); ++y) {
        for (size_t x = 0; x < this->width(); ++x) {
            if (_numbers[y][x] == value) {
                return optional { p_t { x, y } };
            }
        }
    }
    // Not found
    return nullopt;
}

// finds the manhattan distance from the value, if found, to the center
optional<int> Numbers::manhattan(int value)
{
    auto posMaybe = this->find(value);
    if (posMaybe) {
        auto pos = *posMaybe;
        auto c_x = this->width() / 2;
        auto c_y = this->height() / 2;
        auto distance
            = abs(static_cast<int>(pos.first - c_x)) + abs(static_cast<int>(pos.second - c_y));
        return optional { distance };
    }
    // Not found
    return nullopt;
}

// Write the value to the same position as the turtle
bool Numbers::write(Turtle::Turtle* t, int value)
{
    return this->set(static_cast<size_t>(t->x()), static_cast<size_t>(t->y()), value);
}

// Add a twirl, going from the center and out in spirals
optional<Numbers*> Numbers::twirl()
{
    size_t w = this->width();
    size_t h = this->height();
    if (w != h) {
        return nullopt;
    }
    auto counter = 1;

    auto t = Turtle::Turtle(static_cast<int>(w / 2), static_cast<int>(h / 2), 1, 0);
    this->write(&t, counter++);

    // Run the turtle round in circles
    for (size_t i = 0; i < w; ++i) {
        for (uint8_t z = 0; z < 2; ++z) {
            for (size_t x = 0; x < i; ++x) {
                t.move_turn(false);
                if (!this->write(&t, counter++)) {
                    break;
                }
            }
            t.move_turn(true);
            if (!this->write(&t, counter++)) {
                break;
            }
        }
    }
    return optional { this };
}

int Numbers::sum_surrounding(size_t x, size_t y)
{
    optional<int> maybeInt = optional { 0 };
    int sum = 0;
    for (int iy = -1; iy <= 1; ++iy) {
        for (int ix = -1; ix <= 1; ++ix) {
            if (iy == 0 && ix == 0) {
                continue;
            }
            maybeInt = this->get(static_cast<size_t>(x + static_cast<size_t>(ix)),
                static_cast<size_t>(y + static_cast<size_t>(iy)));
            if (maybeInt) {
                sum += *maybeInt;
            }
        }
    }
    return sum;
}

// Add a twirl, going from the center and out in spirals, that also sums the surrounding numbers
optional<Numbers*> Numbers::twirl_sum_surrounding()
{
    size_t w = this->width();
    size_t h = this->height();
    if (w != h) {
        return nullopt;
    }

    auto t = Turtle::Turtle(static_cast<int>(w / 2), static_cast<int>(h / 2), 1, 0);
    this->write(&t, 1);

    // Run the turtle round in circles
    for (size_t i = 0; i < w; ++i) {
        for (uint8_t z = 0; z < 2; ++z) {
            for (size_t x = 0; x < i; ++x) {
                t.move_turn(false);
                if (!this->write(&t, this->sum_surrounding(t.x(), t.y()))) {
                    break;
                }
            }
            t.move_turn(true);
            if (!this->write(&t, this->sum_surrounding(t.x(), t.y()))) {
                break;
            }
        }
    }
    return optional { this };
}

// Add a twirl, going from the center and out in spirals, that also sums the surrounding numbers
optional<int> Numbers::twirl_sum_surrounding_quit_after(int q)
{
    size_t w = this->width();
    size_t h = this->height();
    if (w != h) {
        return nullopt;
    }

    auto t = Turtle::Turtle(static_cast<int>(w / 2), static_cast<int>(h / 2), 1, 0);
    auto value = 1;
    this->write(&t, value);

    // Run the turtle round in circles
    for (size_t i = 0; i < w; ++i) {
        for (uint8_t z = 0; z < 2; ++z) {
            for (size_t x = 0; x < i; ++x) {
                t.move_turn(false);
                value = this->sum_surrounding(t.x(), t.y());
                if (value > q) {
                    return optional { value };
                }
                if (!this->write(&t, value)) {
                    break;
                }
            }
            t.move_turn(true);
            value = this->sum_surrounding(t.x(), t.y());
            if (value > q) {
                return optional { value };
            }
            if (!this->write(&t, value)) {
                break;
            }
        }
    }
    return nullopt; // not found
}

int next_twirl_sum_number(int size, int value)
{
    auto n = Numbers(size);
    return must(n.twirl_sum_surrounding_quit_after(value), -1);
}
