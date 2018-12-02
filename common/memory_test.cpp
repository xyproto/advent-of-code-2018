#include "memory.h"
#include "test.h"
#include "divutils.h"

using std::cout;
using std::vector;

void next_test()
{
    size_t length = 10;
    size_t first_pos = 5;
    for (auto i = first_pos + 1; i < first_pos + length; i++) {
        cout << "next: " << clamp(i, length) << endl;
    }
}

void next_test2()
{
    for (int i = 1; i < 10; i++) {
        cout << "next2: " << must(transform(i, 5, 10)) << endl;
    }
}

int main()
{
    next_test();
    next_test2();

    auto start = vector<int> { 0, 2, 7, 0 };
    auto memory = Memory(start);
    cout << memory.str() << endl;

    equal(must(memory.largest(), memory.NotFound).second, 7);
    equal(memory.must_largest_value(), 7);
    equal(memory.must_largest_position(), static_cast<index_t>(2));

    cout << "BEFORE: " << memory.str() << endl;
    memory.redistribute();
    cout << "AFTER: " << memory.str() << endl;

    memory = Memory(start);
    equal(must(memory.redistribution_number(100)), 5);
    equal(memory.must_redistribution_number(), static_cast<unsigned>(5));

    memory = Memory(vector<int> { 2, 4, 1, 2 });
    equal(memory.redistributions_cached(), static_cast<unsigned>(4));
    equal(memory.re_encounter_iterations(), static_cast<unsigned>(4));

    return 0;
}
