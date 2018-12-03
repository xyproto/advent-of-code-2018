#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "stringutils.h"

using std::nullopt;
using std::optional;
using std::pair;
using std::string;
using std::vector;

using namespace std::literals; // for ""s

// Trim functions from:
// https://stackoverflow.com/a/217605/131264

// trim from start (in place)
void _ltrim(string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) { return !std::isspace(ch); }));
}

// trim from end (in place)
void _rtrim(string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) { return !std::isspace(ch); }).base(),
        s.end());
}

// trim from both ends (in place)
void _trim(string& s)
{
    _ltrim(s);
    _rtrim(s);
}

// trim from start (copying)
const string ltrim(string s)
{
    _ltrim(s);
    return s;
}

// trim from end (copying)
const string rtrim(string s)
{
    _rtrim(s);
    return s;
}

// trim from both ends (copying)
const string trim(string s)
{
    _trim(s);
    return s;
}

// --- end of trim functions from stackoverflow ---

// Split a string into two parts, as a pair
const pair<string, string> split(const string& line, const string& sep)
{
    pair<string, string> retval {};
    bool afterSep = false;
    for (unsigned i = 0; i < len(line); i++) {
        if (i >= len(line)) {
            break;
        }
        if (line[i] == sep[0]) {
            // Found a first match, check the rest
            bool match = true;
            for (unsigned i2 = 0; i2 < len(sep); i2++) {
                if (i + i2 >= len(line) || line[i + i2] != sep[i2]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                afterSep = true;
            }
            i += len(sep);
        }
        if (i >= len(line)) {
            break;
        }
        if (afterSep) {
            retval.second += line[i];
        } else {
            retval.first += line[i];
        }
    }
    return retval;
}

// Trim two strings for leading and trailing spaces. Takes a pair of strings.
const pair<string, string> trimpair(const pair<string, string>& s)
{
    auto [a, b] = s;
    return pair<string, string> { trim(a), trim(b) };
}

// Separate a string into two trimmed fields.
const pair<string, string> twofields(const string& s, const string& sep)
{
    return trimpair(split(s, sep));
}

// Trim all strings in a vector of strings
// Will remove empty elements after trimming if remove_empty is true
const vector<string> trimv(const vector<string> words)
{
    std::vector<string> trimmed_words {};
    string trimmed_word;
    for (const auto& word : words) {
        trimmed_word = trim(word);
        if (len(trimmed_word) > 0) {
            trimmed_words.push_back(trimmed_word);
        }
    }
    return trimmed_words;
}

// Split a string into a vector of strings
vector<string> splitv(const string& line, const string& sep)
{
    std::vector<string> retval { ""s }; // must start with an empty string because of += below
    unsigned retcounter = 0;
    for (unsigned i = 0; i < len(line); i++) {
        if (line[i] == sep[0]) {
            // Found a first match, check the rest
            bool match = true;
            for (unsigned i2 = 0; i2 < len(sep); i2++) {
                if (i + i2 >= len(line) || line[i + i2] != sep[i2]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                retcounter++;
                retval.push_back(""s);
            }
            i += len(sep);
        }
        if (i >= len(line) || retcounter >= retval.size()) {
            break;
        }
        retval[retcounter] += line[i];
    }
    return retval;
}

// Split a string into a words, and also take a char separator
vector<string> splitvc(const string& line, const char sep)
{
    std::vector<string> words;
    auto word = ""s;
    for (const char& letter : line) {
        if (letter == sep) {
            words.push_back(word);
            word = ""s;
            continue;
        }
        word += letter;
    }
    if (word.length() > 0) {
        words.push_back(word);
    }
    return words;
}

// Split a string into words, and also take a string separator
vector<string> words(const string& line, const string& sep) { return trimv(splitv(line, sep)); }

// Split a string into trimmed words, using a char as the separator
vector<string> words(const string& line, const char sep) { return trimv(splitvc(line, sep)); }

// Split a string into words
vector<string> splitc(const string& line) { return splitvc(line, ' '); }

// Count the number of times a word appears in a list of words
unsigned count(const vector<string> words, const string& word)
{
    auto counter = 0;
    for (const string& x : words) {
        if (x == word) {
            counter++;
        }
    }
    return counter;
}

// Count the number of times a char appears in a word
unsigned count(const string& word, const char letter)
{
    auto counter = 0;
    for (const char& x : word) {
        if (x == letter) {
            counter++;
        }
    }
    return counter;
}

// Read in all the lines in a text file.
// Quick and dirty, no particular error checking.
const std::vector<std::string> readlines(const std::string& filename)
{
    std::vector<std::string> lines {};
    std::ifstream infile { filename, std::ifstream::in };
    if (!infile.is_open()) {
        std::cerr << "Could not open "s << filename << std::endl;
        return lines;
    }
    auto line { ""s };
    while (getline(infile, line)) {
        lines.push_back(line);
    }
    return lines;
}

// Check if a vector<string> has the given string
bool has(vector<string> words, const string& word)
{
    for (const auto& w : words) {
        if (w == word) {
            return true;
        }
    }
    return false;
}

// Return the string between two given strigns, reading from left to right
const string between(const string& line, const string& sep1, const string& sep2)
{
    return split(split(line, sep1).second, sep2).first;
}

// Return the string between two chars, reading from left to right
const string between(const string& line, const char sep1, const char sep2)
{
    auto word = ""s;
    bool in_the_word = false;
    for (const char& letter : line) {
        if (letter == sep2) {
            return word;
        }
        if (in_the_word) {
            word += letter;
        }
        if (letter == sep1) {
            in_the_word = true;
            continue;
        }
    }
    return word; // did not find sep2
}

// return the last char
optional<const char> last(const string digits)
{
    auto dl = digits.length();
    if (dl < 1) {
        return nullopt;
    }
    return optional { digits.at(dl - 1) };
}

// check if a string contains a given character
bool contains(const string& s, const char& l)
{
    for (const auto& e : s) {
        if (e == l) {
            return true;
        }
    }
    return false;
}

// mustInt converts a string to an int, with no error handling, only error logging
int mustInt(const string& digits, const unsigned base) noexcept
{
    int n { 0 };
    try {
        n = std::stoi(digits, 0, base);
    } catch (const std::invalid_argument& e) {
        std::cerr << "std::stoi error: invalid argument: " << digits << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "std::stoi error: out of range: " << digits << std::endl;
    }
    return n;
}

// mustUnsignedLong converts a string to an unsigned long, with no error handling, only error
// logging
unsigned long mustUnsignedLong(const string& digits, const unsigned base) noexcept
{
    unsigned long ul { 0 };
    try {
        ul = std::stoul(digits, 0, base);
    } catch (const std::invalid_argument& e) {
        std::cerr << "std::stoul error: invalid argument: " << digits << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "std::stoul error: out of range: " << digits << std::endl;
    }
    return ul;
}
