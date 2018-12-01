#include "program.h"

Program::Program(const vector<int> instructions, ProgramType program_type) {
    _ip = 0;
    _instructions = instructions;
    _program_type = program_type;
}

Program::Program(const string filename, ProgramType program_type) {
    _ip = 0;
    _program_type = program_type;
    string line;
    ifstream infile {filename, ifstream::in};
    if (infile.is_open()) {
        while (getline(infile, line)) {
            _instructions.push_back(stoi(line));
        }
    }
}

void Program::list_instructions() {
    cout << "Instructions:" << endl;
    for (const int &x: _instructions) {
        cout << x << endl;
    }
    cout << "Done listing instructions." << endl;
}

string Program::str() {
    stringstream s;
    s << "[";
    size_t counter = 0;
    for (const int &x: _instructions) {
        if (_ip == counter) {
            s << "(" << x << ")";
        } else {
            s << x;
        }
        if (++counter != _instructions.size()) {
            s << ", ";
        }
    }
    s << "]" << endl;
    return s.str();
}

optional<int> Program::current() {
    if (_ip >= _instructions.size()) {
        return nullopt;
    }
    return optional {_instructions[_ip]};
}

// increase the value at the current position, if possible
bool Program::inc() {
    if (_ip >= _instructions.size()) {
        return false;
    }
    _instructions[_ip]++;
    return true;
}

// decrease the value at the current position, if possible
bool Program::dec() {
    if (_ip <= 0) {
        return false;
    }
    _instructions[_ip]--;
    return true;
}

string Program::get_program_type() {
    switch (_program_type) {
        case part1:
            return "part 1";
        case part2:
            return "part 2";
        default:
            return "unknown";
    }
}

// execute the current instruction
bool Program::execute() {
    auto instr = this->current();
    if (instr) {
        auto offset = *instr;
        switch (_program_type) {
        case part1:
            this->inc();
            break;
        case part2:
            if (offset > 2) {
                this->dec();
            } else {
                this->inc();
            }
            break;
        }
        return this->jump(offset);
    }
    // not a valid instruction at the current location
    _reached_completion = true;
    return false; // could not execute this instruction
}

bool Program::jump(int offset) {
    _ip += offset;
    return (_ip < _instructions.size());
}

// Jump to the next instruction and return false if out of range
bool Program::next() {
    return this->jump(1);
}

// run the entire program, with a maximum number of steps to be executed
int Program::run(const unsigned int max_steps) {
    cout << must(this->current()) << ", " << this->str() << endl;
    unsigned int step_counter = 1;
    _reached_completion = true;
    while (this->execute()) {
        cout << must(this->current()) << ", " << this->str() << endl;
        if (++step_counter == max_steps) {
            _reached_completion = false;
            break;
        }
    }
    if (!_reached_completion && step_counter == max_steps) {
        cout << "stopped at step " << step_counter << " (maximum " << max_steps << " steps)" << endl;
    } else {
        cout << "done at step " << step_counter << endl;
    }
    return step_counter;
}

// run the program silently and potentially in an endless loop
int Program::run() {
    unsigned int step_counter = 1;
    while (this->execute()) {
        step_counter++;
    }
    return step_counter;
}
