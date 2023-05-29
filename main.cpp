#include "Puzzle.hpp"
#include <iostream>
#include <chrono>

using namespace std;

int main()
{
    Puzzle puzzle({{1, 2, 3},
                   {4, 5, 6},
                   {7, 8, 0}},
                   
                   {{1, 2, 3},
                    {4, 5, 6},
                    {7, 8, 0}});

    //puzzle.printState();
    auto start = chrono::steady_clock::now();
    puzzle.shuffle(1000000);
    puzzle.printState();
    puzzle.backTraking();
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    //puzzle.printState();
    cout << chrono::duration<double, milli>(diff).count() << " ms" << endl;

    // int opt = getchar();
    // while (opt != int('q'))
    // {
    //     switch (opt)
    //     {
    //     case 'w':
    //         cout << "up\n";
    //         puzzle.safelyMoveZero(movement::UP);
    //         break;
    //     case 'd':
    //         cout << "right\n";
    //         puzzle.safelyMoveZero(movement::RIGHT);
    //         break;
    //     case 's':
    //         cout << "down\n";
    //         puzzle.safelyMoveZero(movement::DOWN);
    //         break;
    //     case 'a':
    //         cout << "left\n";
    //         puzzle.safelyMoveZero(movement::LEFT);
    //         break;
    //     default:
    //         cout << "unknown\n";
    //     }
    //     puzzle.printState();
    //     opt = getchar();
    // }

   // puzzle.printState();
}
