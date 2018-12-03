#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

using std::nullopt;
using std::optional;
using std::pair;
using std::string;
using std::vector;

using namespace std::literals; // for ""s

// Get the length of anything with .length(), inspired by Go and Python
template <class T> inline auto len(const T& s) { return s.length(); }

// Trim functions from:
// https://stackoverflow.com/a/217605/131264

// trim from start (in place)
void _ltrim(string& s);

// trim from end (in place)
void _rtrim(string& s);

// trim from both ends (in place)
void _trim(string& s);

// trim from start (copying)
const string ltrim(string s);

// trim from end (copying)
const string rtrim(string s);

// trim from both ends (copying)
const string trim(string s);

// --- end of trim functions from stackoverflow ---

// Split a string into two parts, as a pair
const pair<string, string> split(const string& line, const string& sep);

// Trim two strings for leading and trailing spaces. Takes a pair of strings.
const pair<string, string> trimpair(const pair<string, string>& s);

// Separate a string into two trimmed fields.
const pair<string, string> twofields(const string& s, const string& sep);

// Trim all strings in a vector of strings
// Will remove empty elements after trimming if remove_empty is true
const vector<string> trimv(const vector<string> words);

// Split a string into a vector of strings
vector<string> splitv(const string& line, const string& sep);

// Split a string into a words, and also take a char separator
vector<string> splitvc(const string& line, char sep);

// Split a string into words, and also take a string separator
vector<string> words(const string& line, const string& sep = " "s);

// Split a string into trimmed words, and also take a char separator
vector<string> words(const string& line, const char sep = ' ');

// Split a string into words
inline vector<string> splitc(const string& line);

// Count the number of times a word appears in a list of words
unsigned count(const vector<string> words, const string& word);

// Count the number of times a char appears in a word
unsigned count(const string& word, const char letter);

// Read in all the lines in a text file.
// Quick and dirty, no particular error checking.
const std::vector<std::string> readlines(const std::string& filename);

// Check if a vector<string> has the given string
bool has(vector<string> words, const string& word);

// Return the string between two given strigns, reading from left to right
const string between(const string& line, const string& sep1 = " "s, const string& sep2 = " "s);

// Return the string between two chars, reading from left to right
const string between(const string& line, const char sep1 = ' ', const char sep2 = ' ');

// return the last char
optional<const char> last(const string digits);

// check if a string contains a given character
bool contains(const string& s, const char& l);

// mustInt converts a string to an int, with no error handling, only error logging
int mustInt(const string& digits, const unsigned base = 10) noexcept;

// mustUnsignedLong converts a string to an unsigned long, with no error handling, only error
// logging
unsigned long mustUnsignedLong(const string& digits, const unsigned base = 10) noexcept;
