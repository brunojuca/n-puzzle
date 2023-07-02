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
string Puzzle::convertStateToString(const vector<vector<int>>& matrix) {
    stringstream ss;
    for (const vector<int>& row : matrix) {
        for (int num : row) {
            ss << setw(2) << setfill('0') << num << " "; // setw(2) e setfill('0') para garantir que os valores
                                                         // de um dígito sejam preenchidos com zero à esquerda
        }
    }
    return ss.str();
}
vector<vector<int>> Puzzle::getStateFromString(const string& str) {
    vector<vector<int>> matrix(this->n, vector<int>(this->m, 0));
    stringstream ss(str);
    for (int i = 0; i < this->n; ++i) {
        for (int j = 0; j < this->m; ++j) {
            ss >> matrix[i][j];
        }
    }
    return matrix;
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
bool Puzzle::checkParity(){
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

bool Puzzle::backTracking(int depthLimit){
    vector<vector<int>> initial = this->state; // armazena o estado inicial;
    map<vector<vector<int>>, vector<vector<int>>> parentMap; // armazena o nó pai
    set<vector<vector<int>>> openList;
    set<vector<vector<int>>> visitedStates;
    int nodesExpanded = 0;
    parentMap[this->state] = {}; 
    int depth = 0;
    int totalStates = 0;
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
        vector<vector<vector<int>>> path;
        while (this->state != initial) { // enquanto o estado atual não chega no estado inicial
            path.push_back(this->state); // adiciona o estado pai
            this->state = parentMap[this->state]; // estado atual passa a ser o estado pai
        }
        path.push_back(initial);  
        reverse(path.begin(), path.end()); // Inverte ocaminho para obter a ordem correta
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
            if(visitedStates.find(this->state) == visitedStates.end()){ // marca estado como visitado
                    visitedStates.insert(this->state);
            }
            if (openList.find(this->state) == openList.end()) 
            {
                parentMap[this->state] = currentState;
                nodesExpanded++;
                openList.insert(this->state);
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
    int totalNodes = 0; // contabiliza a quantidade de nós pais

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
                    nodesExpanded++;
                    openList.push(this->state); // adiciona na fila de abertos
                    parentMap[this->state] = currentPuzzle; // armazena os filhos do estado pai
                }
                safelyMoveZero({-movement.first, -movement.second}); // desfaz o movimento
            }
        }
        totalNodes++;
        if (currentPuzzle == this->goalState) // se estado atual é o objetivo
        {
            cout << "Solution found" << endl;
            cout << "Expanded states: " << nodesExpanded << endl;
            cout << "Visited States: " << visitedStates.size() << endl;
            cout << "Fator de ramificacao: " << (float)nodesExpanded / (totalNodes ) << endl; // total de nós sucessores / total de nós pais
            vector<vector<vector<int>>> path;
            while (currentPuzzle != initial) { // enquanto o estado atual não chega no estado inicial
                depth++; // a profundidade é do estado inicial até o objetivo.
                path.push_back(currentPuzzle); // adiciona o estado pai
                currentPuzzle = parentMap[currentPuzzle]; // estado atual passa a ser o estado pai
            }
            cout << "Depth: " << depth << endl;

            path.push_back(initial);  
            reverse(path.begin(), path.end()); // Inverte o vetor de caminho para obter a ordem correta
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
bool Puzzle::depthLimitedSearch(int depthLimit,set<vector<vector<int>>> &closedList,stack<vector<vector<int>>> &openList, int depth,
vector<vector<int>> currentState, map<vector<vector<int>>, vector<vector<int>>> &parentMap,int &nodesExpanded )
{
    closedList.insert(currentState);
    if (currentState == this->goalState)
        return true;

    if (depth == depthLimit)
        return false;

    vector<pair<int, int>> movements = {movement::UP, movement::RIGHT, movement::DOWN, movement::LEFT};

    for (pair<int, int> movement : movements)
    {
        if (safelyMoveZero({movement.first, movement.second}))
        {
            if (closedList.find(this->state) == closedList.end())
            {   
                nodesExpanded += 1;
                openList.push(this->state);
                parentMap[this->state] = currentState;
                if (depthLimitedSearch(depthLimit, closedList, openList, depth + 1, this->state, parentMap, nodesExpanded))
                    return true;
            }
            safelyMoveZero({-movement.first, -movement.second});
        }
    }
    return false;
}

bool Puzzle::iterativeDepthSearch(int maxDepth)
{
    set<vector<vector<int>>> closedList;
    stack<vector<vector<int>>> openList;
    vector<vector<int>> initial = this->state; // armazena o estado inicial;
    map<vector<vector<int>>, vector<vector<int>>> parentMap; // armazena o nó pai
    parentMap[this->state] = {}; 
    int nodesExpanded = 0;
    
    for (int depthLimit = 0; depthLimit <= maxDepth; depthLimit++)
    {
        int depth = 0;
        closedList.clear();
        openList = stack<vector<vector<int>>>();
        
        openList.push(this->state);
        while (!openList.empty())
        {
            vector<vector<int>> currentState = openList.top();
            openList.pop();

            if (depthLimitedSearch(depthLimit, closedList, openList, depth, currentState, parentMap, nodesExpanded)){
                cout << "Depth: " << depthLimit << endl;
                cout << "Expanded states: " << nodesExpanded << endl;
                cout << "Visited States: " << closedList.size() << endl; 
                vector<vector<vector<int>>> path;
                while (this->state != initial) { // enquanto o estado atual não chega no estado inicial
                    path.push_back(this->state ); // adiciona o estado pai
                    this->state  = parentMap[this->state ]; // estado atual passa a ser o estado pai
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
                break;
            }
        }
    }
    return false;
}
bool Puzzle::orderedSearch()
{
    struct PuzzleNode {
        Puzzle puzzle; // o motivo de armazenar a classe é para tornar a implementação menos complexa, já que as funções pertence a classe e não à matriz.
        int cost; // custo do estado
        int accumulatedCost; // Custo total acumulado até o nó atual
        int depth; // Profundidade do nó atual
        bool operator<(const PuzzleNode& other) const
        {
            return accumulatedCost > other.accumulatedCost; // Ordena em ordem crescente do custo total
        }
    };

    priority_queue<PuzzleNode> openList; 
    unordered_set<string> closedList; // unordered_set utiliza tabela hash, então é necessário passar uma função hash, porém, para string, o próprio c++
                                      // fornece essa função hash. Por esse motivo foi utilizado string ao invés de matriz.
    string initial = convertStateToString(this->state);
    map<string, string> parentMap; // armazena o nó pai
    string current = convertStateToString(this->state);
    parentMap[current] = {}; 
    int nodesExpanded = 0;
    openList.push({*this, cost(), 0, 0}); // O custo total acumulado inicial é 0
    int maxDepth = 0;
    int totalNodes = 0;
    while (!openList.empty())
    {
        PuzzleNode currentNode = openList.top();
        openList.pop();
        Puzzle currentPuzzle = currentNode.puzzle;
        string currentStateString = currentPuzzle.convertStateToString(currentPuzzle.getState());

        if (currentStateString == currentPuzzle.convertStateToString(currentPuzzle.goalState))
        {
            cout << "Solution found" << endl;
            cout << "Depth: " << maxDepth <<endl;
            cout << "Expanded states: " << nodesExpanded << endl;
            cout << "Visited States: " << closedList.size() <<endl;
            cout << "Cost: " << currentNode.accumulatedCost<<endl;
            cout << "Fator de ramificacao: " << (float)nodesExpanded / totalNodes << endl;
            vector<vector<vector<int>>> path;
            while (currentStateString != initial) { // enquanto o estado atual não chega no estado inicial
                vector<vector<int>> currentState = getStateFromString(currentStateString);
                path.push_back(currentState); // adiciona o estado pai
                currentStateString = parentMap[currentStateString]; // estado atual passa a ser o estado pai
            }
            vector<vector<int>> currentState = getStateFromString(initial);
            path.push_back(currentState);  
            reverse(path.begin(), path.end()); // Inverte o vetor de caminho para obter a ordem correta
            cout << "Path: " << endl;
            for (const auto& state : path) {
                printState2(state);
                cout << endl;
            }
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
                    nodesExpanded++;
                    int childAccumulatedCost = currentNode.accumulatedCost + childPuzzle.cost(); // Atualiza o custo total acumulado com o custo do nó atual
                    int childDepth = currentNode.depth + 1;
                    maxDepth = max(maxDepth, childDepth);
                    openList.push({childPuzzle, childPuzzle.cost(), childAccumulatedCost, childDepth});
                    parentMap[childStateString] = currentStateString;
                }
            }
        }
        totalNodes++;
    }

    return false;
}
bool Puzzle::greedySearch()
{
    struct PuzzleNode {
        Puzzle puzzle;
        int heuristic;
        int depth; // Profundidade do nó atual
        bool operator<(const PuzzleNode& other) const
        {
            return heuristic > other.heuristic; // Ordena em ordem crescente do custo
        }
    };

    priority_queue<PuzzleNode> openList;
    unordered_set<string> closedList;
    string initial = convertStateToString(this->state);
    map<string, string> parentMap; // armazena o nó pai
    string current = convertStateToString(this->state);
    parentMap[current] = {}; 
    int nodesExpanded = 0;
    openList.push({*this, manhattanDistance(), 0});
    int maxDepth = 0;
    int totalNodes = 0;
    while (!openList.empty())
    {
        PuzzleNode currentNode = openList.top(); // seleciona o de menor custo (primeiro da fila)
        openList.pop();
        Puzzle currentPuzzle = currentNode.puzzle;
        string currentStateString = currentPuzzle.convertStateToString(currentPuzzle.getState());
        if (currentStateString == currentPuzzle.convertStateToString(currentPuzzle.goalState))
        {
            cout << "Solution found" << endl;
            cout << "Depth: " << maxDepth <<endl;
            cout << "Expanded states: " << nodesExpanded << endl;
            cout << "Visited States: " << closedList.size() <<endl;
            cout << "Fator de ramificacao: " << (float)nodesExpanded / totalNodes << endl;
            vector<vector<vector<int>>> path;
            while (currentStateString != initial) { // enquanto o estado atual não chega no estado inicial
                vector<vector<int>> currentState = getStateFromString(currentStateString);
                path.push_back(currentState); // adiciona o estado pai
                currentStateString = parentMap[currentStateString]; // estado atual passa a ser o estado pai
            }
            vector<vector<int>> currentState = getStateFromString(initial);
            path.push_back(currentState);  
            reverse(path.begin(), path.end()); // Inverte o vetor de caminho para obter a ordem correta
            cout << "Path: " << endl;
            for (const auto& state : path) {
                printState2(state);
                cout << endl;
            }
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
                    nodesExpanded++;
                    int childDepth = currentNode.depth + 1;
                    maxDepth = max(maxDepth, childDepth);
                    openList.push({childPuzzle, childPuzzle.manhattanDistance(), childDepth});
                    parentMap[childStateString] = currentStateString;
                }
            }
        }
        totalNodes++;
    }
    return false;
}
bool Puzzle::AstarSearch()
{
    struct PuzzleNode {
        Puzzle puzzle;
        int heuristic;
        int cost;
        int depth; // Profundidade do nó atual
        bool operator<(const PuzzleNode& other) const
        {
            return heuristic + cost > other.heuristic + cost; // Ordena em ordem crescente do custo
        }
    };

    priority_queue<PuzzleNode> openList;
    unordered_set<string> closedList;
    string initial = convertStateToString(this->state);
    map<string, string> parentMap; // armazena o nó pai
    string current = convertStateToString(this->state);
    parentMap[current] = {}; 
    int nodesExpanded = 0;
    openList.push({*this, manhattanDistance(), cost(), 0});
    int maxDepth = 0;
    int totalNodes = 0;
    while (!openList.empty())
    {
        PuzzleNode currentNode = openList.top(); // seleciona o de menor custo (primeiro da fila)
        openList.pop();
        Puzzle currentPuzzle = currentNode.puzzle;
        string currentStateString = currentPuzzle.convertStateToString(currentPuzzle.getState());
        if (currentStateString == currentPuzzle.convertStateToString(currentPuzzle.goalState))
        {
            cout << "Solution found" << endl;
            cout << "Depth: " << maxDepth <<endl;
            cout << "Expanded states: " << nodesExpanded << endl;
            cout << "Visited States: " << closedList.size() <<endl;
            cout << "Cost: " << currentNode.cost<< endl;
            cout << "Fator de ramificacao: " << (float)nodesExpanded / totalNodes << endl;
            vector<vector<vector<int>>> path;
            while (currentStateString != initial) { // enquanto o estado atual não chega no estado inicial
                vector<vector<int>> currentState = getStateFromString(currentStateString);
                path.push_back(currentState); // adiciona o estado pai
                currentStateString = parentMap[currentStateString]; // estado atual passa a ser o estado pai
            }
            vector<vector<int>> currentState = getStateFromString(initial);
            path.push_back(currentState);  
            reverse(path.begin(), path.end()); // Inverte o vetor de caminho para obter a ordem correta
            Imprime o caminho
            cout << "Path: " << endl;
            for (const auto& state : path) {
                printState2(state);
                cout << endl;
            }
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
                    nodesExpanded++;
                    int childDepth = currentNode.depth + 1;
                    maxDepth = max(maxDepth, childDepth);
                    int childAccumulatedCost = currentNode.cost + childPuzzle.cost();
                    openList.push({childPuzzle, childPuzzle.manhattanDistance(), childAccumulatedCost, childDepth});
                    parentMap[childStateString] = currentStateString;
                }
            }
        }
        totalNodes++;
    }
    return false;
}

bool Puzzle::IDAstarSearch()
{
    struct PuzzleNode {
        Puzzle puzzle;
        int heuristic;
        int cost;
        int depth;
        bool operator<(const PuzzleNode& other) const
        {
            return heuristic + cost > other.heuristic + other.cost; // Ordena em ordem crescente do custo total
        }
    };
    string initial = convertStateToString(this->state);
    int nodesExpanded = 0;
    
    int maxDepth = 0;
    int patamar = manhattanDistance(); // Limite inicial é a heurística do estado inicial
    while (true)
    {
        int nextPatamar = INT_MAX; // Próximo limite é infinito
        
        priority_queue<PuzzleNode> openList;
        unordered_set<string> closedList;
        
        map<string, string> parentMap; // armazena o nó pai
        string current = convertStateToString(this->state);
        parentMap[current] = {}; 
        int totalNodes = 0;
        int lastPatamarNodesExpanded = 0;
        openList.push({*this, manhattanDistance(), cost(), 0});
        while (!openList.empty())
        {
            PuzzleNode currentNode = openList.top();
            openList.pop();
            Puzzle currentPuzzle = currentNode.puzzle;
            string currentStateString = currentPuzzle.convertStateToString(currentPuzzle.getState());

            if (currentStateString == currentPuzzle.convertStateToString(currentPuzzle.goalState))
            {
                cout << "Solution found" << endl;
                cout << "Depth: " << maxDepth <<endl;
                cout << "Expanded states: " << nodesExpanded << endl;
                cout << "Visited States: " << closedList.size() <<endl;
                cout << "Cost: " << currentNode.cost<<endl;
                cout << "Fator de ramificacao: " << (float)lastPatamarNodesExpanded / totalNodes << endl;
                vector<vector<vector<int>>> path;
                while (currentStateString != initial) { // enquanto o estado atual não chega no estado inicial
                    vector<vector<int>> currentState = getStateFromString(currentStateString);
                    path.push_back(currentState); // adiciona o estado pai
                    currentStateString = parentMap[currentStateString]; // estado atual passa a ser o estado pai
                }
                vector<vector<int>> currentState = getStateFromString(initial);
                path.push_back(currentState);  
                reverse(path.begin(), path.end()); // Inverte o vetor de caminho para obter a ordem correta
                cout << "Path: " << endl;
                for (const auto& state : path) {
                    printState2(state);
                    cout << endl;
                }
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
                        nodesExpanded++;
                        lastPatamarNodesExpanded++;
                        int childDepth = currentNode.depth + 1;
                        maxDepth = max(maxDepth, childDepth);
                        int childAccumulatedCost = currentNode.cost + childPuzzle.cost();
                        openList.push({childPuzzle, childPuzzle.manhattanDistance(), childAccumulatedCost, childDepth});
                        parentMap[childStateString] = currentStateString;
                    }
                }
            }
            totalNodes++;
        }

        if (nextPatamar == INT_MAX)
            return false; // Nenhum caminho encontrado até o próximo limite
        
        patamar = nextPatamar; // Atualiza o limite para o próximo limite calculado
        cout << "patamar: " << patamar << endl;
    }

    return false;
}
