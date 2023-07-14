#include "Puzzle.hpp"
#include <iostream>
#include <chrono>
#include <fstream>
#include <thread>
#include <cmath>
using namespace std;

Puzzle createMatriz(int op)
{

    switch (op)
    {
    case 1:
    {
        Puzzle pz({{1, 2, 3},
                   {4, 5, 6},
                   {7, 8, 0}},

                  {{1, 2, 3},
                   {4, 5, 6},
                   {7, 8, 0}});
        return pz;
    }
    case 2:
    {
        Puzzle pz({{1, 2, 3, 4},
                   {5, 6, 7, 8},
                   {9, 10, 11, 0}},

                  {{1, 2, 3, 4},
                   {5, 6, 7, 8},
                   {9, 10, 11, 0}});
        return pz;
    }
    case 3:
    {
        Puzzle pz({{1, 2, 3, 4},
                   {5, 6, 7, 8},
                   {9, 10, 11, 12},
                   {13, 14, 15, 0}},

                  {{1, 2, 3, 4},
                   {5, 6, 7, 8},
                   {9, 10, 11, 12},
                   {13, 14, 15, 0}});
        return pz;
    }
    default:
    {
        cout << "Opcao invalida. " << endl;
        Puzzle pz({}, {});
        return pz;
    }
    }
    // return pz;
}

int main()
{
    // 8 x 7
    // Puzzle puzzle({
    //     { 1,  2,  3,  4,  5,  6,  7},
    //     { 8,  9, 10, 11, 12, 13, 14},
    //     {15, 16, 17, 18, 19, 20, 21},
    //     {22, 23, 24, 25, 26, 27, 28},
    //     {29, 30, 31, 32, 33, 34, 35},
    //     {36, 37, 38, 39, 40, 41, 42},
    //     {43, 44, 45, 46, 47, 48, 49},
    //     {50, 51, 52, 53, 54, 55,  0}
    // },

    // {
    //     { 1,  2,  3,  4,  5,  6,  7},
    //     { 8,  9, 10, 11, 12, 13, 14},
    //     {15, 16, 17, 18, 19, 20, 21},
    //     {22, 23, 24, 25, 26, 27, 28},
    //     {29, 30, 31, 32, 33, 34, 35},
    //     {36, 37, 38, 39, 40, 41, 42},
    //     {43, 44, 45, 46, 47, 48, 49},
    //     {50, 51, 52, 53, 54, 55,  0}
    // });

    // 7 x 7
    // Puzzle puzzle({
    //         { 1,  2,  3,  4,  5,  6,  7},
    //         { 8,  9, 10, 11, 12, 13, 14},
    //         {15, 16, 17, 18, 19, 20, 21},
    //         {22, 23, 24, 25, 26, 27, 28},
    //         {29, 30, 31, 32, 33, 34, 35},
    //         {36, 37, 38, 39, 40, 41, 42},
    //         {43, 44, 45, 46, 47, 48,  0}
    //     },

    //     {
    //         { 1,  2,  3,  4,  5,  6,  7},
    //         { 8,  9, 10, 11, 12, 13, 14},
    //         {15, 16, 17, 18, 19, 20, 21},
    //         {22, 23, 24, 25, 26, 27, 28},
    //         {29, 30, 31, 32, 33, 34, 35},
    //         {36, 37, 38, 39, 40, 41, 42},
    //         {43, 44, 45, 46, 47, 48,  0}
    //     });

    // 6 x 7
    // Puzzle puzzle({
    //         { 1,  2,  3,  4,  5,  6,  7},
    //         { 8,  9, 10, 11, 12, 13, 14},
    //         {15, 16, 17, 18, 19, 20, 21},
    //         {22, 23, 24, 25, 26, 27, 28},
    //         {29, 30, 31, 32, 33, 34, 35},
    //         {36, 37, 38, 39, 40, 41, 42}
    //     },

    //     {
    //         { 1,  2,  3,  4,  5,  6,  7},
    //         { 8,  9, 10, 11, 12, 13, 14},
    //         {15, 16, 17, 18, 19, 20, 21},
    //         {22, 23, 24, 25, 26, 27, 28},
    //         {29, 30, 31, 32, 33, 34, 35},
    //         {36, 37, 38, 39, 40, 41, 42}
    //     });

    // 6 x 6
    // Puzzle puzzle({
    //         { 1,  2,  3,  4,  5,  6},
    //         { 7,  8,  9, 10, 11, 12},
    //         {13, 14, 15, 16, 17, 18},
    //         {19, 20, 21, 22, 23, 24},
    //         {25, 26, 27, 28, 29, 30},
    //         {31, 32, 33, 34, 35,  0}
    //     },

    //     {
    //         { 1,  2,  3,  4,  5,  6},
    //         { 7,  8,  9, 10, 11, 12},
    //         {13, 14, 15, 16, 17, 18},
    //         {19, 20, 21, 22, 23, 24},
    //         {25, 26, 27, 28, 29, 30},
    //         {31, 32, 33, 34, 35,  0}
    //     });

    // 6 x 5
    // Puzzle puzzle({
    //         { 1,  2,  3,  4,  5},
    //         { 6,  7,  8,  9, 10},
    //         {11, 12, 13, 14, 15},
    //         {16, 17, 18, 19, 20},
    //         {21, 22, 23, 24, 25},
    //         {26, 27, 28, 29,  0}
    //     },

    //     {
    //         { 1,  2,  3,  4,  5},
    //         { 6,  7,  8,  9, 10},
    //         {11, 12, 13, 14, 15},
    //         {16, 17, 18, 19, 20},
    //         {21, 22, 23, 24, 25},
    //         {26, 27, 28, 29,  0}
    //     });

    //    5 x 5
    // Puzzle puzzle({{1, 2, 3, 4, 5},
    //                {6, 7, 8, 9, 10},
    //                {11, 12, 13, 14, 15},
    //                {16, 17, 18, 19, 20},
    //                {21, 22, 23, 24, 0}},

    //               {{1, 2, 3, 4, 5},
    //                {6, 7, 8, 9, 10},
    //                {11, 12, 13, 14, 15},
    //                {16, 17, 18, 19, 20},
    //                {21, 22, 23, 24, 0}});
    // Puzzle puzzle({{1, 2, 3, 4, 5},
    //                {6, 7, 8, 9, 10},
    //                {11, 12, 13, 14, 15},
    //                {16, 17, 18, 19, 0}},

    //               {{1, 2, 3, 4, 5},
    //                {6, 7, 8, 9, 10},
    //                {11, 12, 13, 14, 15},
    //                {16, 17, 18, 19, 0}});

    // Puzzle puzzle({{1, 2},
    //                 {3,0 }},

    //                 {{1, 2},
    //                 {3, 0}});

    // std::ofstream file("output.txt");
    // std::streambuf *original_stdout = std::cout.rdbuf();

    // std::cout.rdbuf(file.rdbuf());
    int numExecutions = 100;
    int totalStatesExpanded = 0;
    int totalStatesVisited = 0;
    int totalDepth = 0;
    int totalCost = 0;
    float totalFactor = 0;
    int totalHeuristc = 0;
    float totalTime = 0;
    // for (int i = 0; i < numExecutions; i++)
    // {
    int op;
    cout << "Escolha o tamanho da matriz: " << endl;
    cout << "[1] 3 x 3" << endl;
    cout << "[2] 3 x 4" << endl;
    cout << "[3] 4 x 4" << endl;
    cin >> op;
    Puzzle puzzle = createMatriz(op);

    int op2 = 10;
    while (op2 != 0)
    {
        cout << "Escolha o algoritmo de busca: " << endl;
        cout << "[1] Backtracking." << endl;
        cout << "[2] Busca em Largura." << endl;
        cout << "[3] Busca em profundidade Limitada." << endl;
        cout << "[4] Busca Ordenada." << endl;
        cout << "[5] Busca Gulosa." << endl;
        cout << "[6] Busca A*." << endl;
        cout << "[7] Busca IDA*." << endl;
        cout << "[0] Sair." << endl;
        cin >> op2;
        switch (op2)
        {
        case 1:
        {
            puzzle.shuffle(100);
            puzzle.printState();
            auto start = chrono::steady_clock::now();
            int distance = puzzle.manhattanDistance(); // calcula a distância de manhattan para usar como um valor aproximado do limite de profundidade
            float K = 2;                               // constante qualquer que serve para ajustar um valor mais aproximado do limite de profundidade
            float depthLimit = K * distance;
            int depth = min((int)depthLimit, 31);
            if (!puzzle.backTracking(depthLimit))
            {
                cout << "solution invalid." << endl;
            }
            else
            {   
                auto end = chrono::steady_clock::now();
                auto diff = end - start;
                totalTime = chrono::duration<double, milli>(diff).count();
                totalStatesExpanded += puzzle.getStateExpanded();
                totalStatesVisited += puzzle.getVisited();
                totalDepth += puzzle.getDepth();
                totalFactor += puzzle.getBranchingFactor();
                cout << "---------- RESULTADO -----------" << endl;
                cout << "Expandidos: " << puzzle.getStateExpanded() << endl;
                cout << "Visitados: " << puzzle.getVisited() << endl;
                cout << "Profundidade: " << puzzle.getDepth() << endl;
                cout << "Fator de ramificacao: " << puzzle.getBranchingFactor() << endl;          
                cout << "Tempo: " << totalTime << endl;
                cout << endl;
            }
        }
        break;
        case 2:
        {
            puzzle.shuffle(1000000);
            puzzle.printState();
            if (puzzle.checkParity())
            {
                auto start = chrono::steady_clock::now();
                if (!puzzle.breadthFirstSearch())
                {
                    cout << "solution invalid." << endl;
                }
                else
                {
                    auto end = chrono::steady_clock::now();
                    auto diff = end - start;
                    totalTime = chrono::duration<double, milli>(diff).count();
                    totalStatesExpanded += puzzle.getStateExpanded();
                    totalStatesVisited += puzzle.getVisited();
                    totalDepth += puzzle.getDepth();
                    totalFactor += puzzle.getBranchingFactor();

                    cout << "---------- RESULTADO -----------" << endl;
                    cout << "Expandidos: " << puzzle.getStateExpanded() << endl;
                    cout << "Visitados: " << puzzle.getVisited() << endl;
                    cout << "Profundidade: " << puzzle.getDepth() << endl;
                    cout << "Fator de ramificacao: " << puzzle.getBranchingFactor() << endl;
                    cout << "Tempo: " << totalTime << endl;
                    cout << endl;

                   
                }
            }
        }

        break;
        case 3:
        {
            puzzle.shuffle(1000000);
            puzzle.printState();
            int depth = op * 40;
            if (puzzle.checkParity())
            {
                auto start = chrono::steady_clock::now();
                if (!puzzle.depthLimitedSearch(depth))
                {
                    cout << "solution invalid." << endl;
                }
                else
                {

                    auto end = chrono::steady_clock::now();
                    auto diff = end - start;
                    totalTime = chrono::duration<double, milli>(diff).count();
                    totalStatesExpanded += puzzle.getStateExpanded();
                    totalStatesVisited += puzzle.getVisited();
                    totalDepth += puzzle.getDepth();
                    totalFactor += puzzle.getBranchingFactor();

                    cout << "---------- RESULTADO -----------" << endl;
                    cout << "Expandidos: " << puzzle.getStateExpanded() << endl;
                    cout << "Visitados: " << puzzle.getVisited() << endl;
                    cout << "Profundidade: " << puzzle.getDepth() << endl;
                    cout << "Fator de ramificacao: " << puzzle.getBranchingFactor() << endl;
                    cout << "Tempo: " << totalTime << endl;
                    cout << endl;

                }
            }
        }

        break;
        case 4:
        {
            puzzle.shuffle(1000000);
            puzzle.printState();
            if (puzzle.checkParity())
            {
                auto start = chrono::steady_clock::now();
                if (!puzzle.orderedSearch())
                {
                    cout << "solution invalid." << endl;
                }
                else
                {
                    auto end = chrono::steady_clock::now();
                    auto diff = end - start;
                    totalTime = chrono::duration<double, milli>(diff).count();
                    totalStatesExpanded += puzzle.getStateExpanded();
                    totalStatesVisited += puzzle.getVisited();
                    totalDepth += puzzle.getDepth();
                    totalCost += puzzle.getAccumulatedCost();
                    totalFactor += puzzle.getBranchingFactor();

                    cout << "---------- RESULTADO -----------" << endl;
                    cout << "Expandidos: " << puzzle.getStateExpanded() << endl;
                    cout << "Visitados: " << puzzle.getVisited() << endl;
                    cout << "Profundidade: " << puzzle.getDepth() << endl;
                    cout << "Fator de ramificacao: " << puzzle.getBranchingFactor() << endl;
                    cout << "Custo: " << puzzle.getAccumulatedCost() << endl;
                    cout << "Tempo: " << totalTime << endl;
                    cout << endl;

                }
            }
        }

        break;
        case 5:
        {
            puzzle.shuffle(1000000);
            puzzle.printState();
            if (puzzle.checkParity())
            {
                auto start = chrono::steady_clock::now();
                if (!puzzle.greedySearch())
                {
                    cout << "solution invalid." << endl;
                }
                else
                {
                    auto end = chrono::steady_clock::now();
                    auto diff = end - start;
                    totalTime = chrono::duration<double, milli>(diff).count();
                    totalStatesExpanded += puzzle.getStateExpanded();
                    totalStatesVisited += puzzle.getVisited();
                    totalDepth += puzzle.getDepth();
                    totalCost += puzzle.getAccumulatedCost();
                    totalFactor += puzzle.getBranchingFactor();

                    cout << "---------- RESULTADO -----------" << endl;
                    cout << "Expandidos: " << puzzle.getStateExpanded() << endl;
                    cout << "Visitados: " << puzzle.getVisited() << endl;
                    cout << "Profundidade: " << puzzle.getDepth() << endl;
                    cout << "Fator de ramificacao: " << puzzle.getBranchingFactor() << endl;
                    cout << "Custo: " << puzzle.getAccumulatedCost() << endl;
                    cout << "Tempo: " << totalTime << endl;
                    cout << endl;
                }
            }
        }

        break;
        case 6:
        {
            puzzle.shuffle(1000000);
            puzzle.printState();
            if (puzzle.checkParity())
            {
                auto start = chrono::steady_clock::now();
                if (!puzzle.AstarSearch())
                {
                    cout << "solution invalid." << endl;
                }
                else{
                    auto end = chrono::steady_clock::now();
                    auto diff = end - start;
                    totalTime = chrono::duration<double, milli>(diff).count();
                    totalStatesExpanded += puzzle.getStateExpanded();
                    totalStatesVisited += puzzle.getVisited();
                    totalDepth += puzzle.getDepth();
                    totalCost += puzzle.getAccumulatedCost();
                    totalFactor += puzzle.getBranchingFactor();

                    cout << "---------- RESULTADO -----------" << endl;
                    cout << "Expandidos: " << puzzle.getStateExpanded() << endl;
                    cout << "Visitados: " << puzzle.getVisited() << endl;
                    cout << "Profundidade: " << puzzle.getDepth() << endl;
                    cout << "Fator de ramificacao: " << puzzle.getBranchingFactor() << endl;
                    cout << "Custo: " << puzzle.getAccumulatedCost() << endl;
                    cout << "Tempo: " << totalTime << endl;
                    cout << endl;
                }
            }
        }

        break;
        case 7:
        {
            puzzle.shuffle(1000000);
            puzzle.printState();
            if (puzzle.checkParity())
            {
                auto start = chrono::steady_clock::now();
                if (!puzzle.IDAstarSearch())
                {
                    cout << "solution invalid." << endl;
                }
                else
                {
                    auto end = chrono::steady_clock::now();
                    auto diff = end - start;
                    totalTime = chrono::duration<double, milli>(diff).count();
                    totalStatesExpanded += puzzle.getStateExpanded();
                    totalStatesVisited += puzzle.getVisited();
                    totalDepth += puzzle.getDepth();
                    totalCost += puzzle.getAccumulatedCost();
                    totalFactor += puzzle.getBranchingFactor();

                    cout << "---------- RESULTADO -----------" << endl;
                    cout << "Expandidos: " << puzzle.getStateExpanded() << endl;
                    cout << "Visitados: " << puzzle.getVisited() << endl;
                    cout << "Profundidade: " << puzzle.getDepth() << endl;
                    cout << "Fator de ramificacao: " << puzzle.getBranchingFactor() << endl;
                    cout << "Custo: " << puzzle.getAccumulatedCost() << endl;
                    cout << "Tempo: " << totalTime << endl;
                    cout << endl;
                }
            }
        }

        break;

        default:
            break;
        }
    }
    // cout << "Estados expandidos: " << totalStatesExpanded / numExecutions << endl;
    // cout << "Estados visitados: " << totalStatesVisited / numExecutions << endl;
    // cout << "Profundidade média: " << round(totalDepth / numExecutions) << endl;
    // cout << "Custo Médio: " << round(totalCost / numExecutions) << endl;
    // cout << "Fator de ramificação: " << (totalFactor / numExecutions) << endl;
    // cout << "Tempo médio: " << totalTime / numExecutions << endl;
    // cout.rdbuf(original_stdout);
    // file.close();
}
