#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>

using namespace std;

namespace movement
{
    const int UP = 0;
    const int RIGHT = 1;
    const int DOWN = 2;
    const int LEFT = 3;
}

class Puzzle
{
private:
    vector<vector<int>> state;
    int zeroRow;
    int zeroColumn;
    int dimension;
    void setZeroPosition();
public:
    Puzzle(vector<vector<int>> state);
    ~Puzzle();
    void printState();
    bool validZeroMovement(int movement);
    void moveZero(int movement);
    bool safelyMoveZero(int movement);
    void shuffle(int moves);

};

#endif