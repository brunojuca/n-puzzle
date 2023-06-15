#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <stack>
#include <unordered_set>
#include <set>
#include <string>
#include <cmath>
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
    set<string> visitedStates;
    stack<string> openList;
    unordered_set<string> closedList;

    int moves;
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

    // funções auxiliares
    string convertStateToString(const vector<vector<int>>& state); // converte a matriz em string
    vector<vector<int>> getStateFromString(const string& stateString); // converte a string em matriz
    int manhattanDistance(); // Heurística: calcula a distância de manhattan que mede a soma das distâncias horizontais e verticais entre cada peça e sua posição final desejada.
    void findGoalPosition(int value, int& row, int& col); //  encontrar a posição correta de cada número no estado objetivo.
    bool checkParity(); // checa paridade
    vector<vector<int>> getState();

    // funções principais
    bool backTracking(int dephtLimit); // backTracking
    bool breadthFirstSearch(); // busca em largura
    bool depthLimitedSearch(int depthLimit); // busca em profundidade limitada
    bool iterativeDepthSearch(int maxDepth); // busca em profundidade iterativa
    bool orderedSearch(); // busca ordenada
    bool greedySearch(); // busca gulosa
};

#endif
