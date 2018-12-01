#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using std::find_if;
using std::ifstream;
using std::isspace;
using std::istringstream;
using std::pair;
using std::string;
using std::vector;

using namespace std::literals; // for ""s

// Trim functions from:
// https://stackoverflow.com/a/217605/131264

// trim from start (in place)
inline void _ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch) {
        return !isspace(ch);
    }));
}

// trim from end (in place)
inline void _rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
inline void _trim(string &s) {
    _ltrim(s);
    _rtrim(s);
}

// trim from start (copying)
inline const string ltrim(string s) {
    _ltrim(s);
    return s;
}

// trim from end (copying)
inline const string rtrim(string s) {
    _rtrim(s);
    return s;
}

// trim from both ends (copying)
inline const string trim(string s) {
    _trim(s);
    return s;
}

// --- end of trim functions from stackoverflow ---

// Get the length of anything with .length(), inspired by Go and Python
template<class T>
inline auto len(const T& s) {
    return s.length();
}

// Split a string into two pairs
const pair<string, string> split(const string& line, const string& sep) {
    pair<string, string> retval {};
    bool afterSep = false;
    for (unsigned i=0; i < len(line); i++) {
        if (i >= len(line)) {
            break;
        }
        if (line[i] == sep[0]) {
            // Found a first match, check the rest
            bool match = true;
            for (unsigned i2=0; i2 < len(sep); i2++) {
                if (i+i2 >= len(line) || line[i+i2] != sep[i2]) {
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

// Trim all strings in a vector of strings
// Will remove empty elements after trimming if remove_empty is true
const vector<string> trimv(const vector<string> words) {
    vector<string> trimmed_words {};
    string trimmed_word;
    for (const auto& word: words) {
        trimmed_word = trim(word);
        if (len(trimmed_word) > 0) {
            trimmed_words.push_back(trimmed_word);
        }
    }
    return trimmed_words;
}

// Split a string into a vector of strings
vector<string> splitv(const string& line, const string& sep) {
    vector<string> retval {""s}; // must start with an empty string because of += below
    unsigned retcounter = 0;
    for (unsigned i=0; i < len(line); i++) {
        if (line[i] == sep[0]) {
            // Found a first match, check the rest
            bool match = true;
            for (unsigned i2=0; i2 < len(sep); i2++) {
                if (i+i2 >= len(line) || line[i+i2] != sep[i2]) {
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
vector<string> splitv(const string& line, char sep) {
    vector<string> words;
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
inline vector<string> words(const string& line, const string& sep) {
    return trimv(splitv(line, sep));
}

// Split a string into trimmed words, and also take a char separator
inline vector<string> words(const string& line, const char sep = ' ') {
    return trimv(splitv(line, sep));
}

// Split a string into a words
inline vector<string> splitc(const string& line) {
    return splitv(line, ' ');
}

// Count the number of times a word appears in a list of words
inline unsigned count(const vector<string> words, const string& word) {
    auto counter = 0;
    for (const string& x : words) {
        if (x == word) {
            counter++;
        }
    }
    return counter;
}

// Count the number of times a char appears in a word
inline unsigned count(const string& word, const char letter) {
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
const vector<string> readlines(const string& filename) {
    vector<string> lines {};
    string line;
    ifstream infile {filename, ifstream::in};
    if (infile.is_open()) {
        while (getline(infile, line)) {
            istringstream is {line};
            lines.push_back(is.str());
        }
    }
    return lines;
}

// Check if a vector<string> has the given string
bool has(vector<string> words, const string& word) {
    for (const auto& w: words) {
        if (w == word) {
            return true;
        }
    }
    return false;
}

// Return the string between two given strigns, reading from left to right
inline const string between(const string& line, const string& sep1 = " "s, const string& sep2 = " "s) {
    return split(split(line, sep1).second, sep2).first;
}

// Return the string between two chars, reading from left to right
inline const string between(const string& line, const char sep1 = ' ', const char sep2 = ' ') {
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

// convert a string to unsigned long
inline unsigned long to_unsigned_long(const string& digits, const unsigned base = 10) {
    return stoul(digits, 0, base);
}
