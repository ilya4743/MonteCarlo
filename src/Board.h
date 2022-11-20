#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "defs.h"

using namespace std;

class Board
{
    int size;

public:
    vector<vector<int>> map;
    Board (int size):size(size),map(size,vector<int>(size,0)){}
    Board (const Board& board):size(board.size),map(board.map){}
    void print();
    bool MakeMove(int __who, int __wherex, int __wherey);
    int CheckWin();
    bool IsPlayable();
    void Init();
    void Init(int size);
    int getSize(){return size;}
    bool setPlayerInput(size_t row, size_t col, CELL currentPlayer);
};
#endif // BOARD_H
