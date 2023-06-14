#include "Puzzle.hpp"
#include <iostream>
#include <chrono>

using namespace std;

int main()
{
    // Puzzle puzzle({{1, 2, 3, 4},
    //                {5, 6, 7, 8},
    //                {9, 10, 11, 12},
    //                {13, 14, 15, 0}},

    //               {{1, 2, 3, 4},
    //                {5, 6, 7, 8},
    //                {9, 10, 11, 12},
    //                {13, 14, 15, 0}});
 Puzzle puzzle({{1, 2, 3},
                {4, 5, 6},
                {7, 8, 0}},

                {{1, 2, 3},
                {4, 5, 6},
                {7, 8, 0}});

    // Teste - Backtracking 
    // auto start = chrono::steady_clock::now();
    // puzzle.shuffle(1000000);
    // puzzle.printState();
    // int distance = puzzle.manhattanDistance(); // calcula a distância de manhattan para usar como um valor aproximado do limite de profundidade
    // float K = 2; // constante qualquer que serve para ajustar um valor mais aproximado do limite de profundidade
    // float depthLimit = K * distance;
    // cout << depthLimit << endl;
    // if (!puzzle.backTracking(depthLimit)){
    //     cout << "solution invalid." << endl;
    // }
    // auto end = chrono::steady_clock::now();
    // auto diff = end - start;
    // cout << chrono::duration<double, milli>(diff).count() << " ms" << endl;

    // Teste - Busca em Largura 
    puzzle.shuffle(1000000);
    puzzle.printState();
    if(puzzle.checkParity()){
        auto start2 = chrono::steady_clock::now();
        if(!puzzle.breadthFirstSearch()){
            cout << "solution invalid." << endl;
        }
        auto end2 = chrono::steady_clock::now();
        auto diff2 = end2 - start2;
        cout << chrono::duration<double, milli>(diff2).count() << " ms" << endl;
    }
    else
        cout << "solution invalid. Parity ímpar." <<endl;

    // Teste - Busca em profundidade
    // puzzle.shuffle(1000000);
    // puzzle.printState();
    // if(puzzle.checkParity()){
    //     auto start3 = chrono::steady_clock::now();
    //     if(!puzzle.iterativeDeepeningSearch(40)){
    //         cout << "solution invalid." << endl;
    //     }
    //     auto end3 = chrono::steady_clock::now();
    //     auto diff3 = end3 - start3;
    //     cout << chrono::duration<double, milli>(diff3).count() << " ms" << endl;
    // }
    // else{
    //     cout << "solution invalid.Parity impar" << endl;
    // }
   

    // int opt = getchar();
    // while (opt != int('q'))
    // {
    //     switch (opt)
    //     {
    //     case 'w':
    //         cout << "up\n";
    //         puzzle.safelyMoveZero(movement::UP);
    //         break;
    //     case 'd':
    //         cout << "right\n";
    //         puzzle.safelyMoveZero(movement::RIGHT);
    //         break;
    //     case 's':
    //         cout << "down\n";
    //         puzzle.safelyMoveZero(movement::DOWN);
    //         break;
    //     case 'a':
    //         cout << "left\n";
    //         puzzle.safelyMoveZero(movement::LEFT);
    //         break;
    //     default:
    //         cout << "unknown\n";
    //     }
    //     puzzle.printState();
    //     cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar o caractere de nova linha (\n)
    //     opt = getchar();
    // }

    // puzzle.printState();
}
