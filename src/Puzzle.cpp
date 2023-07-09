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
#include <iomanip>
#include <list>
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
    this->m = state[0].size();
    this->setZeroPosition();
}

Puzzle::~Puzzle()
{
}

void Puzzle::printState()
{
    // cout << endl;
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
void Puzzle::printState2(const vector<vector<int>> &puzzleState) const
{
    for (const auto &row : puzzleState)
    {
        for (const auto &num : row)
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
string Puzzle::convertStateToString(const vector<vector<int>> &matrix)
{
    stringstream ss;
    for (const vector<int> &row : matrix)
    {
        for (int num : row)
        {
            ss << setw(2) << setfill('0') << num << " "; // setw(2) e setfill('0') para garantir que os valores
                                                         // de um dígito sejam preenchidos com zero à esquerda
        }
    }
    return ss.str();
}
vector<vector<int>> Puzzle::getStateFromString(const string &str)
{
    vector<vector<int>> matrix(this->n, vector<int>(this->m, 0));
    stringstream ss(str);
    for (int i = 0; i < this->n; ++i)
    {
        for (int j = 0; j < this->m; ++j)
        {
            ss >> matrix[i][j];
        }
    }
    return matrix;
}

// Heurística
int Puzzle::manhattanDistance()
{
    int distance = 0;
    for (int i = 0; i < this->n; i++)
    {
        for (int j = 0; j < this->m; j++)
        {
            int value = state[i][j];
            if (value != 0)
            {
                int goalRow, goalCol;
                findGoalPosition(value, goalRow, goalCol);
                distance += abs(i - goalRow) + abs(j - goalCol);
            }
        }
    }

    return distance;
}

void Puzzle::findGoalPosition(int value, int &row, int &col)
{
    // int dimension = goalState.size();

    for (int i = 0; i < this->n; i++)
    {
        for (int j = 0; j < this->m; j++)
        {
            if (goalState[i][j] == value)
            {
                row = i;
                col = j;
                return;
            }
        }
    }
}
bool Puzzle::checkParity()
{
    string stateString = convertStateToString(this->state);
    int inversions = 0;

    for (size_t i = 0; i < stateString.size(); i++)
    {
        for (size_t j = i + 1; j < stateString.size(); j++)
        {
            if (stateString[j] != '00' && stateString[i] != '00' && stateString[i] > stateString[j])
                inversions++;
        }
    }
    if (inversions % 2 == 0)
    {
        //cout << "Parity: Par" << endl;
        return true;
    }
    //else
        //cout << "Parity: Ímpar" << endl;
    return false;
}
vector<vector<int>> Puzzle::getState()
{
    return this->state;
}
int Puzzle::cost() // retorna a quantidade de peças fora do lugar
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

int Puzzle::getDepth()
{
    return this->depthMax;
}
int Puzzle::getStateExpanded()
{
    return this->statesExpanded;
}
int Puzzle::getVisited()
{
    return this->visited;
}
float Puzzle::getBranchingFactor()
{
    return this->branchingFactor;
}

int Puzzle::getAccumulatedCost()
{
    return this->accumulatedCost;
}
float Puzzle::calculateBranchingFactor(const map<vector<vector<int>>, vector<vector<int>>>& parentMap)
{
    int totalNodesExpanded = parentMap.size();  // Total de nós expandidos é igual ao tamanho do parentMap
    int totalChilds = 0;  // Contador de filhos

    for (const auto& pair : parentMap)
        totalChilds += pair.second.size();  // Incrementa o número de escolhas para cada estado

    if (totalNodesExpanded > 0)
        return (float)(totalChilds) / totalNodesExpanded;
    else
        return 0.0f;  // Para evitar divisão por zero
}

bool Puzzle::backTracking(int depthLimit)
{
    vector<vector<int>> initial = this->state;               // armazena o estado inicial;
    map<vector<vector<int>>, vector<vector<int>>> parentMap; // armazena o nó pai
    set<vector<vector<int>>> openList;
    set<vector<vector<int>>> visitedStates;
    visitedStates.insert(this->state);
    int nodesExpanded = 0;
    parentMap[this->state] = {};
    int depth = 0;
    int totalStates = 0;
    return auxBackTracking(depthLimit, initial, parentMap, nodesExpanded, depth, openList, visitedStates);
}

bool Puzzle::auxBackTracking(int depthLimit, vector<vector<int>> initial,
                             map<vector<vector<int>>, vector<vector<int>>> parentMap, int &nodesExpanded, int depth, set<vector<vector<int>>> &openList,
                             set<vector<vector<int>>> &visitedStates)
{
    if (this->state == this->goalState)
    {
        this->statesExpanded = visitedStates.size();
        this->visited = visitedStates.size();
        this->depthMax = depth;
        this->branchingFactor = calculateBranchingFactor(parentMap);
        vector<vector<vector<int>>> path;
        while (this->state != initial)
        {                                         // enquanto o estado atual não chega no estado inicial
            path.push_back(this->state);          // adiciona o estado pai
            this->state = parentMap[this->state]; // estado atual passa a ser o estado pai
        }
        path.push_back(initial);
        reverse(path.begin(), path.end()); // Inverte ocaminho para obter a ordem correta
        // Imprime o caminho
        // cout << "Path: " << endl;
        // for (const auto &state : path)
        // {
        //     printState2(state);
        //     cout << endl;
        // }
        return true;
    }
    if (depth == depthLimit)
        return false;
    vector<pair<int, int>> movements = {movement::UP, movement::RIGHT, movement::DOWN, movement::LEFT};
    for (pair<int, int> movement : movements)
    {
        vector<vector<int>> currentState = this->state;
        if (this->safelyMoveZero({movement.first, movement.second}))
        {
            if (visitedStates.find(this->state) == visitedStates.end())
                visitedStates.insert(this->state);
        
            if (openList.find(this->state) == openList.end())
            {
                parentMap[this->state] = currentState;
                nodesExpanded++;
                openList.insert(this->state);
                if (auxBackTracking(depthLimit, initial, parentMap, nodesExpanded, depth + 1, openList, visitedStates))
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
    openList.push(this->state);          // adiciona o estado atual na lista de abertos
    set<vector<vector<int>>> closedList;
    closedList.insert(this->state);                       // marca o estado atual como visitado
    vector<vector<int>> initial = this->state;               // armazena o estado inicial;
    map<vector<vector<int>>, vector<vector<int>>> parentMap; // armazena o nó pai
    int nodesExpanded = 0;
    int depth = 0;

    parentMap[this->state] = {};
    while (!openList.empty()) // enquando a fila nõa está vazia
    {
        vector<vector<int>> currentPuzzle = openList.front(); // armazena o primeiro da fila
        openList.pop();                                       // deleta o primeiro da fila

        this->state = currentPuzzle; // altera o state da classe para o estado atual
        setZeroPosition();           // encontra a posição zero.

        vector<pair<int, int>> movements = {movement::UP, movement::RIGHT, movement::DOWN, movement::LEFT};
        for (pair<int, int> movement : movements) // itera sobre todos os movimentos
        {
            if (safelyMoveZero({movement.first, movement.second})) // se o movimento é válido
            {
                if (closedList.find(this->state) == closedList.end()) // verifica se já foi visitado
                {
                    nodesExpanded++;
                    openList.push(this->state);             // adiciona na fila de abertos
                    parentMap[this->state] = currentPuzzle; // armazena os filhos do estado pai
                }
                safelyMoveZero({-movement.first, -movement.second}); // desfaz o movimento
            }
        }
        closedList.insert(currentPuzzle);  
        if (currentPuzzle == this->goalState) // se estado atual é o objetivo
        {
            this->statesExpanded = nodesExpanded;
            this->visited = closedList.size();
            this->branchingFactor = calculateBranchingFactor(parentMap); // total de nós sucessores / total de nós pais
            vector<vector<vector<int>>> path;
            while (currentPuzzle != initial)
            {                                             // enquanto o estado atual não chega no estado inicial
                depth++;                                  // a profundidade é do estado inicial até o objetivo.
                path.push_back(currentPuzzle);            // adiciona o estado pai
                currentPuzzle = parentMap[currentPuzzle]; // estado atual passa a ser o estado pai
            }
            this->depthMax = depth;
            path.push_back(initial);
            reverse(path.begin(), path.end()); // Inverte o vetor de caminho para obter a ordem correta
            // cout << "Path: " << endl;
            // for (const auto &state : path)
            // {
            //     printState2(state);
            //     cout << endl;
            // }
            return true;
        }
    }
    return false;
}
bool Puzzle::depthLimitedSearch(int depthLimit)
{
    stack<pair<vector<vector<int>>, int>> openList; 
    openList.push(make_pair(this->state, 0));          
    set<vector<vector<int>>> closedList;
    closedList.insert(this->state);                       
    vector<vector<int>> initial = this->state;               
    map<vector<vector<int>>, vector<vector<int>>> parentMap; 
    int nodesExpanded = 0;
    int depth = 0;

    parentMap[this->state] = {};
    while (!openList.empty()) 
    {
        pair<vector<vector<int>>, int> currentState = openList.top(); 
        vector<vector<int>> currentPuzzle = currentState.first;
        int currentDepth = currentState.second;
        openList.pop();                                       

        this->state = currentPuzzle; 
        setZeroPosition();          
        vector<pair<int, int>> movements = {movement::UP, movement::RIGHT, movement::DOWN, movement::LEFT};
        if(currentDepth <= depthLimit){
            for (pair<int, int> movement : movements) 
            {
                if (safelyMoveZero({movement.first, movement.second})) 
                {
                    if (closedList.find(this->state) == closedList.end()) 
                    {
                        nodesExpanded++;
                        openList.push(make_pair(this->state, currentDepth + 1));             
                        parentMap[this->state] = currentPuzzle; 
                    }
                    safelyMoveZero({-movement.first, -movement.second}); 
                }
            }
            closedList.insert(currentPuzzle);
        }
        if (currentPuzzle == this->goalState) 
        {
            this->statesExpanded = nodesExpanded;
            this->visited = closedList.size();
            this->branchingFactor = calculateBranchingFactor(parentMap); 
            vector<vector<vector<int>>> path;
            while (currentPuzzle != initial)
            {                                                 
                path.push_back(currentPuzzle);            
                currentPuzzle = parentMap[currentPuzzle]; 
            }
            this->depthMax = currentState.second;
            path.push_back(initial);
            reverse(path.begin(), path.end()); 
            // cout << "Path: " << endl;
            // for (const auto &state : path)
            // {
            //     printState2(state);
            //     cout << endl;
            // }
            return true;
        }
    }
    return false;
}
bool Puzzle::orderedSearch()
{
    struct PuzzleNode
    {
        vector<vector<int>> state;  
        int cost;            // custo do estado
        int accumulatedCost; // Custo total acumulado até o nó atual
        int depth;           // Profundidade do nó atual
        bool operator<(const PuzzleNode &other) const
        {
            return accumulatedCost > other.accumulatedCost; // Ordena em ordem crescente do custo total
        }
    };

    priority_queue<PuzzleNode> openList;
    set<vector<vector<int>>> closedList;
    vector<vector<int>> initial = this->state;
    map<vector<vector<int>>, vector<vector<int>>> parentMap; 
    parentMap[this->state] = {};
    int nodesExpanded = 0;
    openList.push({this->state, cost(), cost(), 0});
    while (!openList.empty())
    {
       
        PuzzleNode currentNode = openList.top(); // seleciona o de menor custo (primeiro da fila)
        openList.pop();
        this->state = currentNode.state;
        setZeroPosition();
        vector<vector<int>> currentState = currentNode.state;
       
        vector<pair<int, int>> movements = {movement::UP, movement::RIGHT, movement::DOWN, movement::LEFT};
        for (pair<int, int> movement : movements)
        {
            if (safelyMoveZero({movement.first, movement.second}))
            {
                if (closedList.find(this->state) == closedList.end())
                {
                    nodesExpanded++;
                    int childDepth = currentNode.depth + 1;
                    int childAccumulatedCost = currentNode.accumulatedCost + cost();
                    openList.push({this->state, cost() ,childAccumulatedCost, childDepth});
                    parentMap[this->state] = currentState;
                }
                safelyMoveZero({-movement.first, -movement.second});
            }
        }
        closedList.insert(currentState);
        if (currentState == this->goalState)
        {
            this->statesExpanded = nodesExpanded;
            this->visited = closedList.size();
            this->depthMax = currentNode.depth;
            this->accumulatedCost = currentNode.accumulatedCost;
            this->branchingFactor = calculateBranchingFactor(parentMap);
            vector<vector<vector<int>>> path;
            while (currentState != initial)
            { 
                path.push_back(currentState);           // adiciona o estado pai
                currentState = parentMap[currentState]; // estado atual passa a ser o estado pai
            }
            path.push_back(initial);
            reverse(path.begin(), path.end()); // Inverte o vetor de caminho para obter a ordem correta
            // cout << "Path: " << endl;
            // for (const auto &state : path)
            // {
            //     printState2(state);
            //     cout << endl;
            // }
            return true;
        }

    }
    return false;
}
bool Puzzle::greedySearch()
{
    struct PuzzleNode
    {
        vector<vector<int>> puzzle;
        int heuristic;
        int depth; // Profundidade do nó atual
        bool operator<(const PuzzleNode &other) const
        {
            return heuristic > other.heuristic; // Ordena em ordem crescente do custo
        }
    };

    priority_queue<PuzzleNode> openList;
    set<vector<vector<int>>> closedList;
    vector<vector<int>> initial = this->state;
    map<vector<vector<int>>, vector<vector<int>>> parentMap; 
    parentMap[this->state] = {};
    int nodesExpanded = 0;
    openList.push({this->state, manhattanDistance(), 0});
    while (!openList.empty())
    {
        PuzzleNode currentNode = openList.top(); // seleciona o de menor custo (primeiro da fila)
        cout << currentNode.heuristic << endl;
        openList.pop();
        this->state = currentNode.puzzle;
        setZeroPosition();
        vector<vector<int>> currentState = currentNode.puzzle;
        if (currentState == this->goalState)
        {
            this->statesExpanded = nodesExpanded;
            this->visited = closedList.size();
            this->depthMax = currentNode.depth;
            this->branchingFactor = calculateBranchingFactor(parentMap);
            vector<vector<vector<int>>> path;
            while (currentState != initial)
            { 
                path.push_back(currentState);                      // adiciona o estado pai
                currentState = parentMap[currentState]; // estado atual passa a ser o estado pai
            }
            path.push_back(initial);
            reverse(path.begin(), path.end()); // Inverte o vetor de caminho para obter a ordem correta
            cout << "Path: " << endl;
            for (const auto &state : path)
            {
                printState2(state);
                cout << endl;
            }
            return true;
        }
        vector<pair<int, int>> movements = {movement::UP, movement::RIGHT, movement::DOWN, movement::LEFT};
        for (pair<int, int> movement : movements)
        {
            if (safelyMoveZero({movement.first, movement.second}))
            {
                if (closedList.find(this->state) == closedList.end())
                {
                    nodesExpanded++;
                    int childDepth = currentNode.depth + 1;
                    openList.push({this->state, this->manhattanDistance(), childDepth});
                    parentMap[this->state] = currentState;
                }
                safelyMoveZero({-movement.first, -movement.second});
            }
        }
        closedList.insert(currentState);
    }
    return false;
}
bool Puzzle::AstarSearch()
{
    struct PuzzleNode
    {
        vector<vector<int>> puzzle;
        int heuristic;
        int cost; // custo acumulado
        int depth; // Profundidade do nó atual
        bool operator<(const PuzzleNode &other) const
        {
            return heuristic + cost > other.heuristic + other.cost; // Ordena em ordem crescente do custo
        }
    };

    priority_queue<PuzzleNode> openList;
    set<vector<vector<int>>> closedList;
    vector<vector<int>> initial = this->state;
    map<vector<vector<int>>, vector<vector<int>>> parentMap; 
    parentMap[this->state] = {};
    int nodesExpanded = 0;
    openList.push({this->state, manhattanDistance(), cost(), 0});
    while (!openList.empty())
    {
        PuzzleNode currentNode = openList.top(); // seleciona o de menor custo (primeiro da fila)
        openList.pop();
        this->state = currentNode.puzzle;
        setZeroPosition();
        vector<vector<int>> currentState = currentNode.puzzle;
        if (currentState == this->goalState)
        {
            this->statesExpanded = nodesExpanded;
            this->visited = closedList.size();
            this->depthMax = currentNode.depth;
            this->accumulatedCost = currentNode.cost + currentNode.heuristic;
            this->branchingFactor = calculateBranchingFactor(parentMap);
            vector<vector<vector<int>>> path;
            while (currentState != initial)
            { 
                path.push_back(currentState);           // adiciona o estado pai
                currentState = parentMap[currentState]; // estado atual passa a ser o estado pai
            }
            path.push_back(initial);
            reverse(path.begin(), path.end()); // Inverte o vetor de caminho para obter a ordem correta
            // cout << "Path: " << endl;
            // for (const auto &state : path)
            // {
            //     printState2(state);
            //     cout << endl;
            // }
            return true;
        }
        vector<pair<int, int>> movements = {movement::UP, movement::RIGHT, movement::DOWN, movement::LEFT};
        for (pair<int, int> movement : movements)
        {
            if (safelyMoveZero({movement.first, movement.second}))
            {
                if (closedList.find(this->state) == closedList.end())
                {
                    nodesExpanded++;
                    int childDepth = currentNode.depth + 1;
                    int childAccumulatedCost = currentNode.cost + this->cost();
                    openList.push({this->state, this->manhattanDistance(), childAccumulatedCost, childDepth});
                    parentMap[this->state] = currentState;
                }
                safelyMoveZero({-movement.first, -movement.second});
            }
        }
        closedList.insert(currentState);

    }
    return false;
}

bool Puzzle::IDAstarSearch()
{
    struct PuzzleNode
    {
        vector<vector<int>> puzzle;
        int heuristic;
        int cost;
        int depth;
        bool operator<(const PuzzleNode &other) const
        {
            return heuristic + cost > other.heuristic + other.cost; // Ordena em ordem crescente do custo total
        }
    };
    vector<vector<int>> initial = this->state;
    int patamar = manhattanDistance(); // Limite inicial é a heurística do estado inicial
    while (true)
    {
        int nextPatamar = INT_MAX; // Próximo limite é infinito

        priority_queue<PuzzleNode> openList;
        set<vector<vector<int>>> closedList;
        map<vector<vector<int>>, vector<vector<int>>> parentMap; 
        this->state = initial;
        setZeroPosition();
        parentMap[this->state] = {};
        int nodesExpanded = 0;
        openList.push({this->state, manhattanDistance(), cost(), 0});
        while (!openList.empty())
        {
            PuzzleNode currentNode = openList.top();
            openList.pop();
            this->state = currentNode.puzzle;
            setZeroPosition();
            vector<vector<int>> currentState = currentNode.puzzle;

            if (currentState == this->goalState)
            {
                this->statesExpanded = nodesExpanded;
                this->visited = closedList.size();
                this->depthMax = currentNode.depth;
                this->accumulatedCost = currentNode.cost + currentNode.heuristic;
                this->branchingFactor = calculateBranchingFactor(parentMap);
                vector<vector<vector<int>>> path;
                while (currentState != initial) // enquanto o estado atual não chega no estado inicial
                {
                    path.push_back(currentState);                      // adiciona o estado pai
                    currentState = parentMap[currentState]; // estado atual passa a ser o estado pai
                }
                path.push_back(initial);
                reverse(path.begin(), path.end()); // Inverte o vetor de caminho para obter a ordem correta
                cout << "Path: " << endl;
                for (const auto &state : path)
                {
                    printState2(state);
                    cout << endl;
                }
                return true;
            }

            if (currentNode.heuristic + currentNode.cost > patamar)
            {
                // Atualiza o próximo limite com o menor custo do caminho que excede o limite atual
                nextPatamar = min(nextPatamar, currentNode.heuristic + currentNode.cost);
                break;
            }
            vector<pair<int, int>> movements = {movement::UP, movement::RIGHT, movement::DOWN, movement::LEFT};
            for (pair<int, int> movement : movements)
            {
                if (safelyMoveZero({movement.first, movement.second}))
                {
                    if (closedList.find(this->state) == closedList.end())
                    {
                        nodesExpanded++;
                        int childDepth = currentNode.depth + 1;
                        int childAccumulatedCost = currentNode.cost + this->cost();
                        openList.push({this->state, this->manhattanDistance(), childAccumulatedCost, childDepth});
                        parentMap[this->state] = currentState;
                    }
                    safelyMoveZero({-movement.first, -movement.second});
                }
            }
            closedList.insert(currentState);
        }

        if (nextPatamar == INT_MAX)
            return false;      // Nenhum caminho encontrado até o próximo limite
        patamar = nextPatamar; // Atualiza o limite para o próximo limite calculado
    }

    return false;
}
