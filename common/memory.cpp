#include "memory.h"
#include "divutils.h"

Memory::Memory(vector<int> memory) { _memory = memory; }

// Create an empty memory of size "size"
Memory::Memory(size_t size)
{
    for (size_t x = 0; x < size; x++) {
        _memory.push_back(0);
    }
}

// Return the index and value of the largest value
optional<pair<index_t, int>> Memory::largest()
{
    if (_memory.size() == 0) {
        return nullopt;
    }
    index_t counter = 0;
    auto max_index = counter;
    auto max_value = _memory[max_index];
    for (const int& x : _memory) {
        if (x > max_value) { // Must be > and not >= in order to find the first value that is the
                             // largest, not the final largest one
            max_value = x;
            max_index = counter;
        }
        counter++;
    }
    return optional { pair<index_t, int> { max_index, max_value } };
}

// Return the largest value, or -1 if not found
int Memory::must_largest_value() { return must(this->largest(), this->NotFound).second; }

// Return the largest value, or -1 if not found
index_t Memory::must_largest_position() { return must(this->largest(), this->NotFound).first; }

string Memory::str()
{
    stringstream s;
    s << "[";
    size_t counter = 0;
    for (auto& x : _memory) {
        s << x;
        if (++counter != _memory.size()) {
            s << ", ";
        }
    }
    s << "]";
    return s.str();
}

unsigned Memory::redistribute()
{
    auto counter = 0;
    auto largest_item = this->largest();
    if (largest_item) {
        // it's a *pair
        size_t largest_pos = largest_item->first;
        auto largest_val = largest_item->second;
        // empty the memory location with the first largest value and put it in the pocket
        unsigned pocket = static_cast<unsigned>(largest_val);
        _memory[largest_pos] = 0;

        // cout << "rem " << this->str() << endl;

        size_t length = _memory.size();

        // share the pocket money between all positions that are not the largest value position
        unsigned share = static_cast<unsigned>(
            round(static_cast<double>(pocket) / static_cast<double>(length - 1)));

        // as long as there are enough money in the pocket to redistribute a share of the wealth
        for (size_t i = 1; i < length; i++) {
            auto next_pos_opt = transform(i, largest_pos, length);
            if (!next_pos_opt) {
                continue;
            }
            auto next_pos = *next_pos_opt;
            // Break if we can no longer redistribute a share from the pocket
            if (pocket < share) {
                break;
            }
            // Move a share from the pocket to a memory position
            pocket -= share;
            _memory[next_pos] += share;
            counter++;
        }
        // Move the remaining money to the position of the previously largest value
        _memory[largest_pos] += pocket;
        // counter++;
    }
    return counter;
}

vector<int> Memory::get() { return _memory; }

// Find how many times the largest value can be redistributed without the situation repeating
// itself
optional<unsigned> Memory::redistribution_number(unsigned max_iterations)
{
    auto start_state = _memory;
    vector<vector<int>> seen;
    for (unsigned counter = 1; counter <= max_iterations; counter++) {
        seen.push_back(_memory);
        this->redistribute();
        for (const auto& old : seen) {
            if (old == _memory) {
                // set the state back to what it was
                _memory = start_state;
                // return the number of iterations until the situation repeated itself
                return optional<unsigned> { counter };
            }
        }
    }
    // set the state back to what it was
    _memory = start_state;
    // looped too many times
    return nullopt;
}

// Find how many times the largest value can be redistributed without the situation repeating
// itself Assumes it will work out without ending up in an endless loop (!) or consuming all
// available memory (!)
unsigned Memory::must_redistribution_number()
{
    cout << "fst " << this->str() << endl;
    auto start_state = _memory;
    vector<vector<int>> seen;
    unsigned counter = 0;
    while (true) {
        counter++;
        seen.push_back(_memory);
        this->redistribute();
        cout << "add " << this->str() << endl;
        for (const auto& old : seen) {
            if (_memory == old) {
                cout << "fin " << this->str() << endl;
                // set the state back to what it was
                _memory = start_state;
                // return the number of iterations until a situation repeats itself
                return counter;
            }
        }
    }
}

size_t Memory::hash()
{
    size_t seed = _memory.size();
    for (const auto& i : _memory) {
        seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

// Find the number of loops until the start position is seen again
// This one is much faster than the non-cached version above, at least for the first 100000
// iterations
unsigned Memory::redistributions_cached()
{
    // cout << "fst " << this->str() << endl;
    auto start_state = _memory;
    unordered_map<size_t, vector<int>> memo; // map of state.hash() -> next state
    unsigned counter = 0;
    while (true) {
        counter++;
        auto prev_state = _memory;
        auto search = memo.find(this->hash());
        if (search != memo.end()) {
            // cout << "cache hit" << endl;
            // Found a previous result, use that
            _memory = search->second;
        } else {
            // Run the redistribution algorithm
            this->redistribute();
            // Store the new result
            memo[Memory(prev_state).hash()] = _memory;
        }
        // cout << "add " << this->str() << endl;
        if (_memory == start_state) {
            // cout << "fin " << this->str() << endl;
            // return the number of iterations until the situation is the same as the first one
            return counter;
        }
    }
}

// Find how many times the largest value can be redistributed without the situation repeating
// itself Assumes it will work out without ending up in an endless loop (!) or consuming all
// available memory (!) Counts the actual redistributions, not just a redistribution-session!
unsigned Memory::re_encounter_iterations()
{
    auto start_state = _memory;
    vector<unsigned> seen { static_cast<unsigned>(this->hash()) }; // hashes

    // First find the first repeated state
    while (true) {
        this->redistribute();
        cout << "add " << this->str() << endl;
        unsigned redistributed_hash = this->hash();
        for (const auto& seen_hash : seen) {
            if (redistributed_hash == seen_hash) {
                cout << "!!! " << this->str() << endl; // starting point for counting loops
                // Break out of both loops and keep this state in _memory
                goto OUT;
            }
        }
        // Store the unseen hash
        seen.push_back(static_cast<unsigned>(this->hash()));
    }
OUT:

    // clear hashes
    seen = vector<unsigned> { static_cast<unsigned>(this->hash()) }; // hashes

    // Use this as the new start state
    start_state = _memory;

    // Then count the iterations until the repeated state happens again
    unsigned counter = 0;
    while (true) {
        counter++;
        this->redistribute();
        cout << "add " << this->str() << endl;
        unsigned redistributed_hash = this->hash();
        for (const auto& seen_hash : seen) {
            if (redistributed_hash == seen_hash) {
                cout << "/!! " << this->str() << endl; // end point for counting loops
                cout << "cnt " << counter << endl;
                return counter;
            }
        }
        // Store the unseen hash
        seen.push_back(static_cast<unsigned>(this->hash()));
    }
}
