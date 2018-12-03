#include "test.h"
#include "turtle.h"
#include "vectorfield.h"

using std::cout;
using std::endl;
using std::pair;

void vf_test()
{
    // Create a 3x3 vectorfield
    auto vf = Vectorfield(3, 3);

    // Test basic set and get for the vectorfield
    pair<int, int> v { 1, 1 };
    vf.set(1, 1, v);
    auto maybePair = vf.get(1, 1);
    if (maybePair) {
        equal(*maybePair, v);
    } else {
        cout << "FAIL" << endl;
        exit(EXIT_FAILURE);
    }

    // Output the vectorfield
    cout << vf.str() << endl;
}

void turtle_vf_test()
{
    auto n = Numbers("vectorfield_input.txt");
    cout << n.str() << endl;

    auto vf = Vectorfield(n.width(), n.height());

    auto t = Turtle::Turtle(2, 2, 1, 0);

    cout << "--- A ---" << endl;
    cout << vf.str() << endl;
    vf.write(&t);
    cout << "--- B ---" << endl;
    cout << vf.str() << endl;

    // the left-turn pattern:
    // 1->2: true
    // 2->3: true
    // 3->4: false
    //       true
    //
    // So:  1 1,  0 1  0 1,  0 0 1  0 0 1,  0 0 0 1  0 0 0 1, 0 0 0 0 1  0 0 0 0 1
    //
    for (int i = 0; i < 5; ++i) {
        for (int z = 0; z < 2; ++z) {
            for (int x = 0; x < i; ++x) {
                // cout << "0 ";
                cout << t.str() << endl;
                t.move_turn(false);
                if (!vf.write(&t)) {
                    cout << "break at index out of bounds: " << t.str() << endl;
                    break;
                }
            }
            // cout << "1, ";
            cout << t.str() << endl;
            t.move_turn(true);
            if (!vf.write(&t)) {
                cout << "break at index out of bounds: " << t.str() << endl;
                break;
            }
        }
    }
    cout << t.str() << endl;
    cout << vf.str() << endl;
}

void apply_test()
{
    // Fetch the numbers
    auto n = Numbers("input.txt");
    cout << n.str() << endl;

    // Create a vectorfield of the same size
    auto vf = Vectorfield(n.width(), n.height());
    cout << vf.str() << endl;

    // Twirl the vectorfield, from the center and outwards in spirals
    vf.twirl();
    cout << vf.str() << endl;

    // Reverse the directions
    vf.reverse();
    cout << vf.str() << endl;

    // Apply the vectorfield to the matrix and see what happens
    auto new_n_maybe = vf.apply(n);
    if (new_n_maybe) {
        cout << new_n_maybe->str() << endl;
        cout << "center value: " << new_n_maybe->center() << endl;
    }
}

int main()
{
    vf_test();
    turtle_vf_test();
    apply_test();

    return 0;
}
