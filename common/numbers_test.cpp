#include "numbers.h"
#include "test.h"
#include "util.h"

using std::cout;

void basic_test()
{
    // Create a 3x3 matrix
    auto n = Numbers(3, 3);

    // Test basic set and get for the matrix
    int vi = 1;
    n.set(1, 1, vi);
    auto maybeInt = n.get(1, 1);
    if (maybeInt) {
        equal(*maybeInt, vi);
    } else {
        cout << "FAIL" << endl;
        exit(EXIT_FAILURE);
    }

    // Output the matrix
    cout << n.str() << endl;
}

int mustManhattan(Numbers* n, int value)
{
    auto distanceMaybe = n->manhattan(value);
    if (distanceMaybe) {
        return *distanceMaybe;
    }
    // Not found
    return -1;
}

void manhattan_test()
{
    // Create a matrix, 5x5
    auto n = Numbers(5);
    cout << n.str() << endl;

    // Create a twirl of numbers, from the center and out
    n.twirl();
    cout << n.str() << endl;

    // Check basic manhattan distances
    equal(mustManhattan(&n, 1), 0);
    equal(mustManhattan(&n, 12), 3);
    equal(mustManhattan(&n, 23), 2);

    // maxnum for size 10 is approximately: (10-1)**2
    // so for 1024 to exist, sqrt(1024)+1 should work

    auto n2 = Numbers(sqrt(1024) + 1);
    n2.twirl();
    equal(mustManhattan(&n2, 1), 0);
    equal(mustManhattan(&n2, 12), 3);
    equal(mustManhattan(&n2, 23), 2);
}

void sum_surrounding_test()
{
    auto n3 = Numbers(3);
    n3.set(0, 0, 1);
    n3.set(1, 0, 2);
    n3.set(0, 2, 7);
    equal(n3.sum_surrounding(1, 1), 10);

    equal(next_twirl_sum_number(5, 54), 57);
    equal(next_twirl_sum_number(5, 330), 351);
}

int main()
{
    basic_test();
    manhattan_test();
    sum_surrounding_test();

    return 0;
}
