#include "Puzzle.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <limits.h>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <unordered_set>
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
    this->moves = 0;
}

Puzzle::~Puzzle()
{

}

void Puzzle::printState()
{
    //cout << endl;
   // cout << "Dimension: " << this->dimension << endl;
   // cout << "Zero position: (" << this->zeroPos.first << ", " << this->zeroPos.second << ")" << endl;
   // cout << endl;
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
string Puzzle::convertStateToString(const vector<vector<int>>& state)
{
   string stateString = "";
    for (vector<int> row : state)
    {
        for (int num : row)
        {
            stateString += to_string(num);
        }
    }
    return stateString;
}
// Heurística
int Puzzle::manhattanDistance() { 
        int distance = 0;
        int dimension = state.size();

        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                int value = state[i][j];
                if (value != 0) {
                    int goalRow, goalCol;
                    findGoalPosition(value, goalRow, goalCol);
                    distance += abs(i - goalRow) + abs(j - goalCol);
                }
            }
        }

        return distance;
}

void Puzzle::findGoalPosition(int value, int& row, int& col) { 
    int dimension = goalState.size();

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (goalState[i][j] == value) {
                row = i;
                col = j;
                return;
            }
        }
    }
}
vector<vector<int>> Puzzle::getStateFromString(const string& stateString)
{
    vector<vector<int>> aux_state;
    int n = sqrt(stateString.size());
    int index = 0;

    for (int i = 0; i < n; ++i)
    {
        vector<int> row;
        for (int j = 0; j < n; ++j)
        {
            int num = stateString[index++] - '0';
            row.push_back(num);
        }
        aux_state.push_back(row);
    }

    return aux_state;
}
bool Puzzle::checkParity(){
     string stateString = convertStateToString(this->state);
    int inversions = 0;
    
    for (size_t i = 0; i < stateString.size(); i++)
    {
        for (size_t j = i + 1; j < stateString.size(); j++)
        {
            if (stateString[j] != '0' && stateString[i] != '0' && stateString[i] > stateString[j])
                inversions++;
        }
    }
    
    if (inversions % 2 == 0){
        cout << "Parity: Par" << endl;
        return true;    
    }
    else
        cout << "Parity: Ímpar" << endl;
    return false;
}

bool Puzzle::backTracking(int depthLimit)
{   
    if (this->state == this->goalState)
    {
        cout << "Solution found:" << endl;
        this->printState();
        cout << "Moves: " << this->moves << endl;
        return true;
    }
    if(depthLimit == 0) return false;
    vector<pair<int, int>> movements = {movement::UP, movement::RIGHT, movement::DOWN, movement::LEFT};

    for (pair<int, int> movement : movements)
    {
        if(this->safelyMoveZero({movement.first, movement.second}))
        {
            string stateString = convertStateToString(this->state);
            
            if (visitedStates.find(stateString) == visitedStates.end())  // Verifica se o estado já foi visitado
            {
                visitedStates.insert(stateString);  // Adiciona o estado ao conjunto de estados visitados
                this->moves += 1;
                if (this->backTracking(depthLimit - 1))
                {
                    return true;
                }
                visitedStates.erase(stateString); 
            }
            this->safelyMoveZero({-movement.first, -movement.second});
        }
        
    }
    return false; 
}

// bool Puzzle::breadthFirstSearch()
// {
//     queue<Puzzle> openList;
//    // unordered_set<string> closedList;
//     unordered_set<string> statesVisited;
//     openList.push(*this);
//     statesVisited.insert(convertStateToString(this->state));
//     while (!openList.empty())
//     {
//         Puzzle currentPuzzle = openList.front();
//         openList.pop();
        
//         vector<pair<int, int>> movements = {movement::UP, movement::RIGHT, movement::DOWN, movement::LEFT};
//         for (pair<int, int> movement : movements)
//         {
//             Puzzle childPuzzle = currentPuzzle;
            
//             if (childPuzzle.safelyMoveZero({movement.first, movement.second}))
//             {
//                 string childStateString = convertStateToString(childPuzzle.state);
//                 if (visitedStates.find(childStateString) == visitedStates.end())
//                 {
//                     this->moves += 1;
//                     openList.push(childPuzzle);
//                     visitedStates.insert(childStateString);
//                 }
//             }
//         }
//        // closedList.insert(convertStateToString(currentPuzzle.state));
//         if (currentPuzzle.state == goalState)
//         {
//             cout << "Solution found:" << endl;
//             currentPuzzle.printState();
//             cout << "Moves: "<< this->moves << endl;
//             return true;
//         }
//     }
    
//     return false;
// }
bool Puzzle::breadthFirstSearch()
{
    queue<string> openList;
   // unordered_set<string> closedList;
    unordered_set<string> statesVisited;
    openList.push(convertStateToString(this->state));
    statesVisited.insert(convertStateToString(this->state));
    while (!openList.empty())
    {
        string currentPuzzle = openList.front();
        openList.pop();
        this->state.clear();
        vector<vector<int>> currentState = getStateFromString(currentPuzzle);
        for (const auto& vetor_interno : currentState) {
            this->state.push_back(vetor_interno);
        }
        cout << endl <<  "current state: " << currentPuzzle << endl;
        printState();
        vector<pair<int, int>> movements = {movement::UP, movement::RIGHT, movement::DOWN, movement::LEFT};
        for (pair<int, int> movement : movements)
        {
            Puzzle aux = *this;
            aux.state = currentState;
            cout << "aux State: ";
            aux.printState();
            if (aux.safelyMoveZero({movement.first, movement.second}))
            {
                string childStringPuzzle = convertStateToString(aux.state);
                cout << "childStringPuzzle: " << childStringPuzzle << endl;
                //printState();
                if (visitedStates.find(childStringPuzzle) == visitedStates.end())
                {
                    this->moves += 1;
                    openList.push(childStringPuzzle);
                    visitedStates.insert(childStringPuzzle);
                }
            }
        }

        if (currentPuzzle == convertStateToString(goalState))
        {
            cout << "Solution found:" << endl;
            printState();
            cout << "Moves: "<< this->moves << endl;
            return true;
        }
    }
    
    return false;
}
bool Puzzle::depthLimitedSearch(int depthLimit)
{
    string currentStateString = convertStateToString(this->state);
    if (currentStateString == convertStateToString(this->goalState))
        return true;

    if (depthLimit <= 0)
        return false;

    closedList.insert(currentStateString);
    
    vector<pair<int, int>> movements = {movement::UP, movement::RIGHT, movement::DOWN, movement::LEFT};

    for (pair<int, int> movement : movements)
    {
        if (validZeroMovement(movement))
        {
            moveZero(movement);
           // printState();
            string nextStateString = convertStateToString(this->state);
            if (closedList.find(nextStateString) == closedList.end())
            {
                this->moves += 1;
                openList.push(nextStateString);
                if (depthLimitedSearch(depthLimit - 1))
                    return true;
            }
            moveZero({-movement.first, -movement.second});
        }
    }

    return false;
}

bool Puzzle::iterativeDepthSearch(int maxDepth)
{
    for (int depthLimit = 0; depthLimit <= maxDepth; depthLimit++)
    {
        closedList.clear();
        openList = stack<string>();
        
        openList.push(convertStateToString(this->state));
        while (!openList.empty())
        {
            string currentStateString = openList.top();
            openList.pop();
            getStateFromString(currentStateString);

            if (currentStateString == convertStateToString(this->goalState)){
                this->printState();
                return true;
            
            }

            closedList.insert(currentStateString);
            if (depthLimitedSearch(depthLimit)){
                this->printState();
                cout << "DepthLimit: " << depthLimit << endl;
                cout << "moves: " << this->moves << endl;
                return true;
                break;
            }
        }
    }

    return false;
}
vector<vector<int>> Puzzle::getState(){
    return this->state;
}
bool Puzzle::orderedSearch()
{
    struct PuzzleNode {
        Puzzle puzzle;
        int cost;
        int accumulatedCost; // Custo total acumulado até o nó atual

        bool operator<(const PuzzleNode& other) const
        {
            return accumulatedCost > other.accumulatedCost; // Ordena em ordem crescente do custo total
        }
    };

    priority_queue<PuzzleNode> openList;
    unordered_set<string> closedList;

    openList.push({*this, manhattanDistance(), 0}); // O custo total acumulado inicial é 0

    while (!openList.empty())
    {
        PuzzleNode currentNode = openList.top();
        openList.pop();
        Puzzle currentPuzzle = currentNode.puzzle;
        string currentStateString = currentPuzzle.convertStateToString(currentPuzzle.getState());

        if (currentStateString == currentPuzzle.convertStateToString(currentPuzzle.goalState))
        {
            cout << "Solution found:" << endl;
            currentPuzzle.printState();
            cout << "Moves: " << currentPuzzle.moves << endl;
            return true;
        }
        closedList.insert(currentStateString);

        vector<pair<int, int>> movements = {movement::UP, movement::RIGHT, movement::DOWN, movement::LEFT};
        for (pair<int, int> movement : movements)
        {
            Puzzle childPuzzle = currentPuzzle;
            if (childPuzzle.safelyMoveZero({movement.first, movement.second}))
            {
                string childStateString = childPuzzle.convertStateToString(childPuzzle.getState());
                if (closedList.find(childStateString) == closedList.end())
                {
                    childPuzzle.moves++;
                    int childAccumulatedCost = currentNode.accumulatedCost + currentNode.cost; // Atualiza o custo total acumulado com o custo do nó atual
                    openList.push({childPuzzle, childPuzzle.manhattanDistance(), childAccumulatedCost});
                }
            }
        }
    }

    return false;
}

bool Puzzle::greedySearch()
{
    struct PuzzleNode {
        Puzzle puzzle;
        int heuristic;

        bool operator<(const PuzzleNode& other) const
        {
            return heuristic > other.heuristic; // Ordena em ordem crescente do custo
        }
    };

    priority_queue<PuzzleNode> openList;
    unordered_set<string> closedList;

    openList.push({*this, manhattanDistance()});
    while (!openList.empty())
    {
        PuzzleNode currentNode = openList.top(); // seleciona o de menor custo (primeiro da fila)
        openList.pop();
        Puzzle currentPuzzle = currentNode.puzzle;
        string currentStateString = currentPuzzle.convertStateToString(currentPuzzle.getState());
        if (currentStateString == currentPuzzle.convertStateToString(currentPuzzle.goalState))
        {
            cout << "Solution found:" << endl;
            currentPuzzle.printState();
            cout << "Moves: " << currentPuzzle.moves << endl;
            return true;
        }

        closedList.insert(currentStateString);

        vector<pair<int, int>> movements = {movement::UP, movement::RIGHT, movement::DOWN, movement::LEFT};
        for (pair<int, int> movement : movements)
        {
            Puzzle childPuzzle = currentPuzzle;
            if (childPuzzle.safelyMoveZero({movement.first, movement.second}))
            {
                string childStateString = childPuzzle.convertStateToString(childPuzzle.getState());
                if (closedList.find(childStateString) == closedList.end())
                {
                    currentPuzzle.moves++;
                    openList.push({childPuzzle, childPuzzle.manhattanDistance()});
                }
            }
        }
    }
    return false;
}