#include "Puzzle.hpp"
#include <iostream>

using namespace std;

int main()
{
    Puzzle puzzle({{1, 2, 3},
                   {4, 5, 6},
                   {7, 8, 0}});

    puzzle.printState();
    puzzle.shuffle(100);
    puzzle.printState();

    int opt = getchar();
    while (opt != int('q'))
    {
        switch (opt)
        {
        case 'w':
            cout << "up\n";
            puzzle.safelyMoveZero(movement::UP);
            break;
        case 'd':
            cout << "right\n";
            puzzle.safelyMoveZero(movement::RIGHT);
            break;
        case 's':
            cout << "down\n";
            puzzle.safelyMoveZero(movement::DOWN);
            break;
        case 'a':
            cout << "left\n";
            puzzle.safelyMoveZero(movement::LEFT);
            break;
        default:
            cout << "unknown\n";
        }
        puzzle.printState();
        opt = getchar();
    }

    puzzle.printState();
}
