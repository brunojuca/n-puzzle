#include "Puzzle.hpp"
#include <iostream>
#include <chrono>
#include <fstream>
#include <thread>
#include <cmath>
using namespace std;

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
    //  Puzzle puzzle({{1, 2, 3, 4},
    //                 {5, 6, 7, 8},
    //                 {9, 10, 11, 12},
    //                 {13, 14, 15, 0}},

    //                 {{1, 2, 3, 4},
    //                 {5, 6, 7, 8},
    //                 {9, 10, 11, 12},
    //                 {13, 14, 15, 0}});
    // Puzzle puzzle({{1, 2, 3, 4},
    //               {5, 6, 7, 8},
    //               {9, 10, 11, 0}},

    //                 {{1, 2, 3, 4},
    //                 {5, 6, 7, 8},
    //                 {9, 10, 11, 0}});

    Puzzle puzzle({{1, 2, 3},
                   {4, 5, 6},
                   {7, 8, 0}},

                  {{1, 2, 3},
                   {4, 5, 6},
                   {7, 8, 0}});
    std::ofstream file("output.txt");
    std::streambuf *original_stdout = std::cout.rdbuf();

    std::cout.rdbuf(file.rdbuf());
    int numExecutions = 1;
    // puzzle.shuffle(1000000);
    int totalStatesExpanded = 0;
    int totalStatesVisited = 0;
    int totalDepth = 0;
    int totalCost = 0;
    float totalFactor = 0;
    int totalHeuristc = 0;
    float totalTime = 0;
    for (int i = 0; i < numExecutions; i++)
    {

        // this_thread::sleep_for(std::chrono::seconds(1)); // Para não gerar os mesmos estados
        // // -------------------------------------------------- BackTracking ---------------------------------------------
        // auto start = chrono::steady_clock::now();
        // puzzle.printState();
        // int distance = puzzle.manhattanDistance(); // calcula a distância de manhattan para usar como um valor aproximado do limite de profundidade
        // float K = 2; // constante qualquer que serve para ajustar um valor mais aproximado do limite de profundidade
        // float depthLimit = K * distance;
        // int depth = min((int)depthLimit,31);
        // if (!puzzle.backTracking(depthLimit)){
        //     cout << "solution invalid." << endl;
        //     i--;
        // }
        // else{
        //     totalStatesExpanded+= puzzle.getStateExpanded();
        //     totalStatesVisited += puzzle.getVisited();
        //     totalDepth += puzzle.getDepth();
        //     totalFactor += puzzle.getBranchingFactor();
        //     auto end = chrono::steady_clock::now();
        //     auto diff = end - start;
        //     totalTime += chrono::duration<double, milli>(diff).count();
        // }
        // -------------------------------------------------- Busca em Largura ---------------------------------------------
        // puzzle.shuffle(1000000);
        // puzzle.printState();
        // if(puzzle.checkParity()){
        //     auto start = chrono::steady_clock::now();
        //     if(!puzzle.breadthFirstSearch()){
        //         cout << "solution invalid." << endl;
        //     }
        //     else{
        //         totalStatesExpanded+= puzzle.getStateExpanded();
        //         totalStatesVisited += puzzle.getVisited();
        //         totalDepth += puzzle.getDepth();
        //         totalFactor += puzzle.getBranchingFactor();
        //         auto end = chrono::steady_clock::now();
        //         auto diff = end - start;
        //         totalTime += chrono::duration<double, milli>(diff).count();
        //     }
        // }
        // else
        //     i--;

        // -------------------------------------------------- Busca em Profundidade limitada ---------------------------------------------
        // puzzle.shuffle(1000000);
        // //int distance = puzzle.manhattanDistance(); // calcula a distância de manhattan para usar como um valor aproximado do limite de profundidade
        // //float K = 2; // constante qualquer que serve para ajustar um valor mais aproximado do limite de profundidade
        // //float depthLimit = K * distance;
        // //int depth = min((int)depthLimit,30);
        // if(puzzle.checkParity()){
        //     auto start = chrono::steady_clock::now();
        //     if(!puzzle.depthLimitedSearch(40)){
        //         cout << "solution invalid." << endl;
        //         i--;
        //     }
        //     else{
        //         totalStatesExpanded+= puzzle.getStateExpanded();
        //         totalStatesVisited += puzzle.getVisited();
        //         totalDepth += puzzle.getDepth();
        //         totalFactor += puzzle.getBranchingFactor();
        //         auto end = chrono::steady_clock::now();
        //         auto diff = end - start;
        //         totalTime += chrono::duration<double, milli>(diff).count();
        //     }
        // }
        // else
        //     i--;
        // -------------------------------------------------- Busca Ordenada ---------------------------------------------
        // puzzle.shuffle(1000000);
        // puzzle.printState();
        // if(puzzle.checkParity()){
        //     auto start = chrono::steady_clock::now();
        //     if(!puzzle.orderedSearch()){
        //         cout << "solution invalid." << endl;
        //         i--;
        //     }
        //     else{
        //         totalStatesExpanded+= puzzle.getStateExpanded();
        //         totalStatesVisited += puzzle.getVisited();
        //         totalDepth += puzzle.getDepth();
        //         totalCost += puzzle.getAccumulatedCost();
        //         totalFactor += puzzle.getBranchingFactor();
        //         auto end = chrono::steady_clock::now();
        //         auto diff = end - start;
        //         totalTime += chrono::duration<double, milli>(diff).count();
        //     }
        // }
        // else
        //     i--;

        // -------------------------------------------------- Busca Gulosa ---------------------------------------------

        puzzle.shuffle(1000000);
        puzzle.printState();
        if (puzzle.checkParity())
        {
            auto start = chrono::steady_clock::now();
            if (!puzzle.greedySearch())
            {
                cout << "solution invalid." << endl;
                i--;
            }
            else
            {
                totalStatesExpanded += puzzle.getStateExpanded();
                totalStatesVisited += puzzle.getVisited();
                totalDepth += puzzle.getDepth();
                totalCost += puzzle.getAccumulatedCost();
                totalFactor += puzzle.getBranchingFactor();
                auto end = chrono::steady_clock::now();
                auto diff = end - start;
                totalTime += chrono::duration<double, milli>(diff).count();
            }
        }
        else
            i--;

        // -------------------------------------------------- Busca A* ---------------------------------------------
        // Resolve até 7x7 dependendo da sua quantidade de memória e da configuração do N-puzzle
        // puzzle.shuffle(1000000);
        // puzzle.printState();
        // if (puzzle.checkParity())
        // {
        //     auto start = chrono::steady_clock::now();
        //     if (!puzzle.AstarSearch())
        //     {
        //         cout << "solution invalid." << endl;
        //     }
        //     totalStatesExpanded+= puzzle.getStateExpanded();
        //     totalStatesVisited += puzzle.getVisited();
        //     totalDepth += puzzle.getDepth();
        //     totalCost += puzzle.getAccumulatedCost();
        //     totalFactor += puzzle.getBranchingFactor();
        //     auto end = chrono::steady_clock::now();
        //     auto diff = end - start;
        //     totalTime += chrono::duration<double, milli>(diff).count();
        // }
        // else
        //     i--;

        // -------------------------------------------------- Busca IDA* ---------------------------------------------
        // puzzle.shuffle(1000000);
        // puzzle.printState();
        // if (puzzle.checkParity())
        // {
        //     auto start = chrono::steady_clock::now();
        //     if (!puzzle.IDAstarSearch())
        //     {
        //         cout << "solution invalid." << endl;
        //         i--;
        //     }
        //     else{
        //         totalStatesExpanded+= puzzle.getStateExpanded();
        //         totalStatesVisited += puzzle.getVisited();
        //         totalDepth += puzzle.getDepth();
        //         totalCost += puzzle.getAccumulatedCost();
        //         totalFactor += puzzle.getBranchingFactor();
        //         auto end = chrono::steady_clock::now();
        //         auto diff = end - start;
        //         totalTime += chrono::duration<double, milli>(diff).count();
        //     }
        // }
        // else
        //     i--;
    }
    cout << "Estados expandidos: " << totalStatesExpanded / numExecutions << endl;
    cout << "Estados visitados: " << totalStatesVisited / numExecutions << endl;
    cout << "Profundidade média: " << round(totalDepth / numExecutions) << endl;
    cout << "Custo Médio: " << round(totalCost / numExecutions) << endl;
    cout << "Fator de ramificação: " << (totalFactor / numExecutions) << endl;
    cout << "Tempo médio: " << totalTime / numExecutions << endl;
    cout.rdbuf(original_stdout);
    file.close();
}
