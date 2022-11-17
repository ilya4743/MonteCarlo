#ifndef TICTACTOE_GAME
#define TICTACTOE_GAME

#include <iostream>
using namespace std;

#define TTT_EMPTY           0
#define TTT_CROSS           1
#define TTT_CIRCLE          2

#define TTT_FIELDSIZE       3

namespace TTTGame
{
    typedef int Field [TTT_FIELDSIZE][TTT_FIELDSIZE];

    void Init ( Field & __field );
    void Print ( Field & __field );
    bool MakeMove ( Field & __field, int __who, int __wherex, int __wherey );
    int CheckWin ( Field & __field );
    bool IsPlayable ( Field & __field );

}

#endif
