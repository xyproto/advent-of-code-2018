#pragma once

#include "util.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::nullopt;
using std::string;
using std::stringstream;
using std::vector;

using position_t = unsigned int;
using counter_t = unsigned int;

enum ProgramType { part1, part2 };

class Program {

private:
    vector<int> _instructions;
    position_t _ip; // "instruction pointer";
    bool _reached_completion;
    ProgramType _program_type;

public:
    Program(const vector<int> instructions, ProgramType program_type);
    Program(const string filename, ProgramType program_type);
    void list_instructions();
    string str();
    optional<int> current();
    bool jump(int offset);
    bool next();
    bool execute();
    bool inc();
    bool dec();
    int run(const unsigned int max_steps);
    int run(); // run silently and potentially in an endless loop
    string get_program_type();
};
