#pragma once

#include <optional>
#include <vector>

using std::nullopt;
using std::optional;
using std::string;
using std::vector;

using namespace std::literals;

// return the last char
optional<const char> last(const string digits);

// must deal with signed ints for the < 0 check to work
// returns an unsigned int
// is not really clamping, since i is wrapped around instead of clamped
template <typename T, typename U> constexpr T clamp(U i, T length)
{
    U signed_length = static_cast<U>(length); // used for dealing with "i" below
    while (i < 0) {
        i += signed_length;
    }
    while (i >= signed_length) {
        i -= signed_length;
    }
    return static_cast<T>(i);
}

// Check if a vector contains an element
template <typename T> auto contains(vector<T> l, T e)
{
    for (const T& x : l) {
        if (x == e) {
            return true;
        }
    }
    return false;
}

// convert from 0,1,2,3,4 to for instance 6,7,8,9,0
// offset is the offset of the new range
// i is the input value (a counter from 0 and up, for example)
// length is the total length of the range
// exclude is an output value that should not be returned, but make the function return nullopt
template <typename T>
optional<T> transform(const T i, const int offset, const T length, const T exclude)
{
    auto v = clamp(i + offset, length);
    if (v == exclude) {
        return nullopt;
    }
    return optional<T> { v };
}

// Same as the transform above, but the offset is used as the value to exclude
template <typename T> optional<T> transform(const T i, const int offset, const T length)
{
    auto v = clamp(i + offset, length);
    if (v == static_cast<T>(offset)) {
        return nullopt;
    }
    return optional<T> { v };
}

// Return the optional value, or the notFoundValue if not
template <typename T> T must(optional<T> maybeT, T notFoundValue)
{
    if (maybeT) {
        return *maybeT;
    }
    return notFoundValue;
}

// Return the integer value, or -1 if nullopt
constexpr int must(optional<int> maybeInt)
{
    if (maybeInt) {
        return *maybeInt;
    }
    return -1;
}
