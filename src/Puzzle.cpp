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
#include <map>
#include <sstream>
using namespace std;

Puzzle::Puzzle(vector<vector<int>> state, vector<vector<int>> goalState)
{
    for (vector<int> row : state)
        if (row.size() != state[0].size())
            throw invalid_argument("The state vector must have 2 dimensions of same size");

    for (vector<int> row : goalState)
        if (row.size() != goalState[0].size())
            throw invalid_argument("The goal state vector must have 2 dimensions of same size");

    if (state.size() != goalState.size() || state[0].size() != goalState[0].size())
            throw invalid_argument("The state vector and the goal state vector must have equal dimensions");

    this->state = state;
    this->goalState = goalState;
    this->n = state.size();
    this->m = state[0].size();;
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
void Puzzle::printState2(const vector<vector<int>>& puzzleState) const
{
    for (const auto& row : puzzleState)
    {
        for (const auto& num : row)
        {
            cout << num << " ";
        }
        cout << endl;
    }
}

void Puzzle::setZeroPosition()
{
    for (size_t i = 0; i < this->n; i++)
        for (size_t j = 0; j < this->m; j++)
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
    if (newPos.first >= 0 && newPos.first < this->n && newPos.second >= 0 && newPos.second < this->m)
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
    if (newPos.first >= 0 && newPos.first < this->n && newPos.second >= 0 && newPos.second < this->m)
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
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->m; j++) {
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
    //int dimension = goalState.size();

    for (int i = 0; i < this->n; i++) {
        for (int j = 0; j < this->m; j++) {
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
vector<vector<int>> Puzzle::getState(){
    return this->state;
}
int Puzzle::cost() // retorna a quantidade de peçasfora do lugar
{
    int count = 0;
    for (int i = 0; i < this->n; i++)
    {
        for (int j = 0; j < this->m; j++)
        {
            if (state[i][j] != goalState[i][j])
            {
                count++;
            }
        }
    }
    return count;
}

bool Puzzle::backTracking(int depthLimit){
    vector<vector<int>> initial = this->state; // armazena o estado inicial;
    map<vector<vector<int>>, vector<vector<int>>> parentMap; // armazena o nó pai
    set<vector<vector<int>>> openList;
    set<vector<vector<int>>> visitedStates;
    int nodesExpanded = 0;
    parentMap[this->state] = {}; 
    int depth = 0;
    return auxBackTracking(depthLimit,initial,parentMap,nodesExpanded, depth, openList, visitedStates);
}

bool Puzzle::auxBackTracking(int depthLimit, vector<vector<int>> initial,
 map<vector<vector<int>>, vector<vector<int>>> parentMap, int &nodesExpanded, int depth, set<vector<vector<int>>> &openList,
     set<vector<vector<int>>> &visitedStates)
{   
    if (this->state == this->goalState)
    {
        cout << "Solution found:" << endl;
        this->printState();
        cout << "Nodes Expanded: " << nodesExpanded << endl;
        cout << "Visited States: " << visitedStates.size() << endl;
        cout << "Depth: " << depth << endl;
        //imprimir o caminho
        vector<vector<vector<int>>> path;
        while (this->state != initial) { // enquanto o estado atual não chega no estado inicial
            path.push_back(this->state); // adiciona o estado pai
            this->state = parentMap[this->state]; // estado atual passa a ser o estado pai
        }
        path.push_back(initial);  
        reverse(path.begin(), path.end()); // Inverte o vetor de caminho para obter a ordem correta
        // Imprime o caminho
        cout << "Path: " << endl;
        for (const auto& state : path) {
            printState2(state);
            cout << endl;
        }
        return true;
    }
    if(depth == depthLimit) return false;
    vector<pair<int, int>> movements = {movement::UP, movement::RIGHT, movement::DOWN, movement::LEFT};
    for (pair<int, int> movement : movements)
    {
        vector<vector<int>> currentState = this->state;
        if(this->safelyMoveZero({movement.first, movement.second}))
        { 
            if(visitedStates.find(this->state) == visitedStates.end()){
                    visitedStates.insert(this->state);
            }
            if (openList.find(this->state) == openList.end())  // Verifica se o estado já foi visitado
            {
                parentMap[this->state] = currentState;
                nodesExpanded++;
                openList.insert(this->state);
                  // Adiciona o estado ao conjunto de estados visitados
                if (auxBackTracking(depthLimit,initial, parentMap, nodesExpanded, depth + 1, openList, visitedStates))
                {
                    return true;
                }
                    openList.erase(this->state);
            }
            this->safelyMoveZero({-movement.first, -movement.second});
        }
    }
    return false; 
}

bool Puzzle::breadthFirstSearch()
{
    queue<vector<vector<int>>> openList; // lista de abertos
    openList.push(this->state); // adiciona o estado atual na lista de abertos
    set<vector<vector<int>>> visitedStates;
    visitedStates.insert(this->state); // marca o estado atual como visitado
    vector<vector<int>> initial = this->state; // armazena o estado inicial;
    map<vector<vector<int>>, vector<vector<int>>> parentMap; // armazena o nó pai
    int nodesExpanded = 0;
    int depth = 0;
    parentMap[this->state] = {}; 
    while (!openList.empty()) // enquando a fila nõa está vazia
    {
        vector<vector<int>> currentPuzzle = openList.front(); // armazena o primeiro da fila
        visitedStates.insert(currentPuzzle); // marca como visitado
        openList.pop(); // deleta o primeiro da fila
        
        this->state = currentPuzzle; // altera o state da classe para o estado atual
        setZeroPosition(); // encontra a posição zero.

        vector<pair<int, int>> movements = {movement::UP, movement::RIGHT, movement::DOWN, movement::LEFT};
        for (pair<int, int> movement : movements) // itera sobre todos os movimentos
        {
            if (safelyMoveZero({movement.first, movement.second})) // se o movimento é válido
            {
                if (visitedStates.find(this->state) == visitedStates.end()) // verifica se já foi visitado
                {
                    //this->moves += 1;
                    nodesExpanded++;
                    openList.push(this->state); // adiciona na fila de abertos
                    parentMap[this->state] = currentPuzzle; // armazena os filhos do estado pai
                }
                safelyMoveZero({-movement.first, -movement.second}); // desfaz o movimento
            }
        }
        if (currentPuzzle == this->goalState) // se estado atual é o objetivo
        {
            cout << "Solution found:" << endl;
            //printState();
            //cout << "Moves: "<< this->moves << endl;
            cout << "Nodes Expanded: " << nodesExpanded << endl;
            cout << "Visited States: " << visitedStates.size() << endl;
            cout << "Depth: " << depth << endl;
            // imprimir o caminho
            vector<vector<vector<int>>> path;
            while (currentPuzzle != initial) { // enquanto o estado atual não chega no estado inicial
                path.push_back(currentPuzzle); // adiciona o estado pai
                currentPuzzle = parentMap[currentPuzzle]; // estado atual passa a ser o estado pai
            }
            path.push_back(initial);  
            reverse(path.begin(), path.end()); // Inverte o vetor de caminho para obter a ordem correta
            // Imprime o caminho
            cout << "Path: " << endl;
            for (const auto& state : path) {
                printState2(state);
                cout << endl;
            }
            return true;
        }
    }
    return false;
}
// bool Puzzle::iterativeDepthSearch(int maxDepth)
// {
//     for (int depthLimit = 0; depthLimit <= maxDepth; depthLimit++)
//     {
//         closedList.clear();
//         openList = stack<string>();
        
//         openList.push(this->state);
//         while (!openList.empty())
//         {
//             vector<vector<int>> currentState = openList.top();
//             openList.pop();

//             if (currentState == this->goalState){
//                 this->printState();
//                 return true;
//             }

//             closedList.insert(currentState);
//             if (depthLimitedSearch(depthLimit)){
//                 this->printState();
//                 cout << "DepthLimit: " << depthLimit << endl;
//                 cout << "moves: " << this->moves << endl;
//                 return true;
//                 break;
//             }
//         }
//     }

//     return false;
// }
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

    openList.push({*this, cost(), 0}); // O custo total acumulado inicial é 0

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
                    int childAccumulatedCost = currentNode.accumulatedCost + childPuzzle.cost(); // Atualiza o custo total acumulado com o custo do nó atual
                    openList.push({childPuzzle, childPuzzle.cost(), childAccumulatedCost});
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
bool Puzzle::AstarSearch()
{
    struct PuzzleNode {
        Puzzle puzzle;
        int heuristic;
        int cost;

        bool operator<(const PuzzleNode& other) const
        {
            return heuristic + cost > other.heuristic + cost; // Ordena em ordem crescente do custo
        }
    };

    priority_queue<PuzzleNode> openList;
    unordered_set<string> closedList;

    openList.push({*this, manhattanDistance(), cost()});
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
                    openList.push({childPuzzle, childPuzzle.manhattanDistance(), childPuzzle.cost()});
                }
            }
        }
    }
    return false;
}

bool Puzzle::IDAstarSearch()
{
    struct PuzzleNode {
        Puzzle puzzle;
        int heuristic;
        int cost;

        bool operator<(const PuzzleNode& other) const
        {
            return heuristic + cost > other.heuristic + other.cost; // Ordena em ordem crescente do custo total
        }
    };

    int patamar = manhattanDistance(); // Limite inicial é a heurística do estado inicial
    while (true)
    {
        int nextPatamar = INT_MAX; // Próximo limite é infinito
        
        priority_queue<PuzzleNode> openList;
        unordered_set<string> closedList;

        openList.push({*this, manhattanDistance(), 0});

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

            if (currentNode.heuristic + currentNode.cost > patamar)
            {
                // Atualiza o próximo limite com o menor custo do caminho que excede o limite atual
                nextPatamar = min(nextPatamar, currentNode.heuristic + currentNode.cost);
                continue;
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
                        openList.push({childPuzzle, childPuzzle.manhattanDistance(), childPuzzle.cost()});
                    }
                }
            }
        }

        if (nextPatamar == INT_MAX)
            return false; // Nenhum caminho encontrado até o próximo limite

        patamar = nextPatamar; // Atualiza o limite para o próximo limite calculado
    }

    return false;
}
