#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>

using namespace std;

namespace movement
{
    const pair<int, int> UP = pair<int, int>(-1, 0);
    const pair<int, int> RIGHT = pair<int, int>(0, 1);
    const pair<int, int> DOWN = pair<int, int>(1, 0);
    const pair<int, int> LEFT = pair<int, int>(0, -1);
}

class Puzzle
{
private:
    vector<vector<int>> state;
    vector<vector<int>> goalState;
    pair<int, int> zeroPos = make_pair(0, 0);
    int dimension;
    void setZeroPosition();

public:
    Puzzle(vector<vector<int>> state, vector<vector<int>> goalState);
    ~Puzzle();
    void printState();
    bool validZeroMovement(pair<int, int> movement);
    void moveZero(pair<int, int> movement);
    bool safelyMoveZero(pair<int, int> movement);
    void shuffle(int moves);
};

#endif