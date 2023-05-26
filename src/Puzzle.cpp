#include "Puzzle.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

Puzzle::Puzzle(vector<vector<int>> state)
{
    for (vector<int> row : state)
        if (row.size() != state.size())
            throw invalid_argument("The vector must have 2 dimensions of same size");

    this->state = state;
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
    cout << "Zero position: (" << this->zeroRow << ", " << this->zeroColumn << ")" << endl;
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
                this->zeroRow = i;
                this->zeroColumn = j;
                return;
            }
        }
}

bool Puzzle::validZeroMovement(int movement)
{
    switch (movement)
    {
    case movement::UP:
        if (this->zeroRow > 0)
            return true;
        break;
    case movement::RIGHT:
        if (this->zeroColumn < this->dimension - 1)
            return true;
        break;
    case movement::DOWN:
        if (this->zeroRow < this->dimension - 1)
            return true;
        break;
    case movement::LEFT:
        if (this->zeroColumn > 0)
            return true;
        break;
    default:
        return false;
        break;
    }
    return false;
}

void Puzzle::moveZero(int movement)
{
    switch (movement)
    {
    case movement::UP:
        this->state[this->zeroRow][this->zeroColumn] = this->state[this->zeroRow - 1][this->zeroColumn];
        this->state[this->zeroRow - 1][this->zeroColumn] = 0;
        this->zeroRow--;
        break;
    case movement::RIGHT:
        this->state[this->zeroRow][this->zeroColumn] = this->state[this->zeroRow][this->zeroColumn + 1];
        this->state[this->zeroRow][this->zeroColumn + 1] = 0;
        this->zeroColumn++;

        break;
    case movement::DOWN:
        this->state[this->zeroRow][this->zeroColumn] = this->state[this->zeroRow + 1][this->zeroColumn];
        this->state[this->zeroRow + 1][this->zeroColumn] = 0;
        this->zeroRow++;
        break;
    case movement::LEFT:
        this->state[this->zeroRow][this->zeroColumn] = this->state[this->zeroRow][this->zeroColumn - 1];
        this->state[this->zeroRow][this->zeroColumn - 1] = 0;
        this->zeroColumn--;
        break;
    default:
        break;
    }
}

bool Puzzle::safelyMoveZero(int movement)
{
    switch (movement)
    {
    case movement::UP:
        if (this->zeroRow > 0)
        {
            this->state[this->zeroRow][this->zeroColumn] = this->state[this->zeroRow - 1][this->zeroColumn];
            this->state[this->zeroRow - 1][this->zeroColumn] = 0;
            this->zeroRow--;
            return true;
        }
        break;
    case movement::RIGHT:
        if (this->zeroColumn < this->dimension - 1)
        {
            this->state[this->zeroRow][this->zeroColumn] = this->state[this->zeroRow][this->zeroColumn + 1];
            this->state[this->zeroRow][this->zeroColumn + 1] = 0;
            this->zeroColumn++;
            return true;
        }
        break;
    case movement::DOWN:
        if (this->zeroRow < this->dimension - 1)
        {
            this->state[this->zeroRow][this->zeroColumn] = this->state[this->zeroRow + 1][this->zeroColumn];
            this->state[this->zeroRow + 1][this->zeroColumn] = 0;
            this->zeroRow++;
            return true;
        }
        break;
    case movement::LEFT:
        if (this->zeroColumn > 0)
        {
            this->state[this->zeroRow][this->zeroColumn] = this->state[this->zeroRow][this->zeroColumn - 1];
            this->state[this->zeroRow][this->zeroColumn - 1] = 0;
            this->zeroColumn--;
            return true;
        }
        break;
    default:
        return false;
        break;
    }
    return false;
}

void Puzzle::shuffle(int moves)
{
    srand((unsigned)time(NULL));
    int madeMoves = 0;
    while (madeMoves < moves)
        if (this->safelyMoveZero(rand() % 4))
            madeMoves++;
}