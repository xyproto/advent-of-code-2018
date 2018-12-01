#include "util.h"

using std::string;
using std::optional;
using std::nullopt;

// return the last char
optional<const char> last(const string digits) {
    auto dl = digits.length();
    if (dl < 1) {
        return nullopt;
    }
    return optional {digits.at(dl - 1)};
}
