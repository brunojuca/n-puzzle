#include "Puzzle.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

Puzzle::Puzzle(vector<vector<int>> state, vector<vector<int>> goalState)
{
    for (vector<int> row : state)
        if (row.size() != state.size())
            throw invalid_argument("The state vector must have 2 dimensions of same size");

    for (vector<int> row : goalState)
        if (row.size() != goalState.size())
            throw invalid_argument("The goal state vector must have 2 dimensions of same size");

    if (state.size() != goalState.size())
            throw invalid_argument("The state vector and the goal state vector must have equal dimensions");

    this->state = state;
    this->goalState = goalState;
    this->dimension = state.size();
    this->setZeroPosition();
}

Puzzle::~Puzzle()
{
}

void Puzzle::printState()
{
    cout << endl;
    cout << "Dimension: " << this->dimension << endl;
    cout << "Zero position: (" << this->zeroPos.first << ", " << this->zeroPos.second << ")" << endl;
    cout << endl;
    for (vector row : this->state)
    {
        for (int num : row)
        {
            cout << num << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Puzzle::setZeroPosition()
{
    for (size_t i = 0; i < this->dimension; i++)
        for (size_t j = 0; j < this->dimension; j++)
        {
            if (this->state[i][j] == 0)
            {
                this->zeroPos.first = i;
                this->zeroPos.second = j;
                return;
            }
        }
}

bool Puzzle::validZeroMovement(pair<int, int> movement)
{
    pair<int, int> newPos = pair<int, int>(this->zeroPos.first + movement.first, this->zeroPos.second + movement.second);
    if (newPos.first >= 0 && newPos.first < this->dimension && newPos.second >= 0 && newPos.second < this->dimension)
        return true;
    return false;
}

void Puzzle::moveZero(pair<int, int> movement)
{
    pair<int, int> newPos = pair<int, int>(this->zeroPos.first + movement.first, this->zeroPos.second + movement.second);
    this->state[this->zeroPos.first][this->zeroPos.second] = this->state[newPos.first][newPos.second];
    this->state[newPos.first][newPos.second] = 0;
    this->zeroPos = newPos;
}

bool Puzzle::safelyMoveZero(pair<int, int> movement)
{
    pair<int, int> newPos = pair<int, int>(this->zeroPos.first + movement.first, this->zeroPos.second + movement.second);
    if (newPos.first >= 0 && newPos.first < this->dimension && newPos.second >= 0 && newPos.second < this->dimension)
    {
        this->state[this->zeroPos.first][this->zeroPos.second] = this->state[newPos.first][newPos.second];
        this->state[newPos.first][newPos.second] = 0;
        this->zeroPos = newPos;
        return true;
    }
    return false;
}

void Puzzle::shuffle(int moves)
{
    srand((unsigned)time(NULL));
    vector<pair<int, int>> movements = {movement::UP, movement::RIGHT, movement::DOWN, movement::LEFT};
    int madeMoves = 0;
    while (madeMoves < moves)
    {
        this->safelyMoveZero(movements[rand() % 4]);
        madeMoves++;
    }
}

bool Puzzle::backTraking()
{
    if (this->state == this->goalState)
    {
        cout << "Solution found:" << endl;
        this->printState();
        return true;
    }

    vector<pair<int, int>> movements = {movement::UP, movement::RIGHT, movement::DOWN, movement::LEFT};

     for (pair<int, int> movement : movements)
    {
        if (this->validZeroMovement(movement))
        {
            this->moveZero(movement);

            if (!isVisitedState(this->state))
            {
                addVisitedState(this->state);
                if (this->backTraking())
                    return true;
                removeVisitedState(this->state);
            }
            this->moveZero({-movement.first, -movement.second});
        }
    }
    return false; 
}

bool Puzzle::isVisitedState(vector<vector<int>> &state)
{
    vector<int> flatState;
        for (const auto& row : state) {
            flatState.insert(flatState.end(), row.begin(), row.end());
        }
        return find(visitedStates.begin(), visitedStates.end(), flatState) != visitedStates.end();
}
void Puzzle::addVisitedState( vector<vector<int>>& state)
{
    vector<int> flatState;
        for (const auto& row : state) {
            flatState.insert(flatState.end(), row.begin(), row.end());
        }
        visitedStates.push_back(flatState);
}
void Puzzle::removeVisitedState( vector<vector<int>>& state)
{
    vector<int> flatState;
        for (const auto& row : state) {
            flatState.insert(flatState.end(), row.begin(), row.end());
        }
        visitedStates.erase(remove_if(visitedStates.begin(), visitedStates.end(), [&flatState](const std::vector<int>& s) {
            return s == flatState;
        }), visitedStates.end());
}