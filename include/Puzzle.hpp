#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <stack>
#include <unordered_set>
#include <set> // uma lista que impede valores duplicados
#include <string>
#include <cmath>
#include <map>
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
    int n;
    int m;
    void setZeroPosition();
    int depthMax;
    int statesExpanded;
    int visited;
    float branchingFactor;
    int accumulatedCost;
public:
    Puzzle(vector<vector<int>> state, vector<vector<int>> goalState);
    ~Puzzle();
    void printState();
    void printState2(const vector<vector<int>>& puzzleState)const;
    bool validZeroMovement(pair<int, int> movement);
    void moveZero(pair<int, int> movement);
    bool safelyMoveZero(pair<int, int> movement);
    void shuffle(int moves);

    // funções auxiliares
    string convertStateToString(const vector<vector<int>>& state); // converte a matriz em string
    vector<vector<int>> getStateFromString(const string& stateString); // converte a string em matriz
    int manhattanDistance(); // Heurística: calcula a distância de manhattan que mede a soma das distâncias horizontais e verticais entre cada peça e sua posição final desejada.
    void findGoalPosition(int value, int& row, int& col); //  encontrar a posição correta de cada número no estado objetivo.
    bool checkParity(); // checa paridade
    vector<vector<int>> getState(); // retorna o estado
    int cost(); // retorna a quantidade de peças fora do lugar - Custo
    int getDepth();
    int getStateExpanded();
    int getVisited();
    float getBranchingFactor();
    int getAccumulatedCost();
    float calculateBranchingFactor(const map<vector<vector<int>>, vector<vector<int>>>& parentMap);

    // funções principais
    bool backTracking(int dephtLimit);
    bool auxBackTracking(int dephtLimit,vector<vector<int>> initial, map<vector<vector<int>>,vector<vector<int>>> parentMap, 
    int &nodesExpanded, int depth,  set<vector<vector<int>>> &openList, set<vector<vector<int>>> &visitedStates); // backTracking
    bool breadthFirstSearch(); 
    bool depthLimitedSearch(int depthLimit);
    bool orderedSearch(); 
    bool greedySearch(); 
    bool AstarSearch(); 
    bool IDAstarSearch(); 
};

#endif
