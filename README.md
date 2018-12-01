# Advent of Code 2018

Solutions for Advent of Code 2018 in C++17.

The solution with the highest number is always a "work in progress".

## Requirements

* g++ (GCC) or clang++ (Clang) with support for C++17.
* [sakemake](https://github.com/xyproto/sakemake)

## Building and running

Enter the desired day and part:

    cd d1p1

Then build and run:

    sm run

Alternatively, something like this may work:

    g++ -std=c++17 -O2 -DDATADIR=\"data/\" -I../include ../common/numbers.cpp ../common/turtle.cpp main.cpp -o d1p1 && ./d1p1

## Workflow for new challenges

1. Create a directory for the challenge in question, for day 4 part 2 create a directory named `d4p2`.
2. Create `main.cpp` from scratch, or copy it from a previous challenge.
3. If the challenge comes with one or more data files, place them in a directory named `data` inside the `d4p2` directory.
4. When reading files from within `main.cpp` refer to the `DATADIR` define, with a space before the filename string. For example: `openFile(DATADIR "input.txt"s);`. `openFile` and `input.txt` are made-up names. The string literal `"s` is optional.
5. See if any of the functions available in `../common` may be applicable for solving the current challenge. Browsing the headers in `../include` may give a better overview (and have more informative comments).
6. If needed, add a function to `../include` and `../common` by first adding the function signature and/or header-only functions in a header file in `../include` and then adding the implementation in a `.cpp` file with the same first name in `../common`. Add a test-cpp file in `../common` by naming it the first name of the file then `_test.cpp`, so that the test file for `bananas.cpp` is `bananas_test.cpp`. Follow the pattern of the other `*_test.cpp` files. `sm test` can be used for running tests in a directory with `_test.cpp` files.
7. Solve the challenge. Adding common functions and classes, with tests that make sure they work correctly, is helpful.
8. The `sm` command can be used for building and `sm run` can be used for building and running. `sm rebuild` rebuilds. There is also support for profiling and debug builds. See the [sakemake](https://github.com/xyproto/sakemake) webpage for more information.
9. Generating project files for QtCreator with `sm pro`, then opening it in `qtcreator`, can be useful for debugging.
10. `sm fmt` can be used for formatting the source code. QtCreator can also be configured to ie. format all C++ code with the clang-format style of WebKit, with 99 character long lines.

## General info

* License: MIT
