#ifndef MONTECARLOBOT
#define MONTECARLOBOT

#include <iostream>
#include <vector>
using namespace std;

#include "Player.h"
#include "TicTacToeGame.h"

typedef struct MCBTreeNode
{
    int Player      = 0;

    int MoveX       = -1;
    int MoveY       = -1;

    int Wins        = 0;
    int Attempts    = 0;

    MCBTreeNode * Parent      = nullptr;
    vector <MCBTreeNode *> Nodes;
} MCBTreeNode;

class MonteCarloBot : public Player
{
private:
    int mFigure;
    TTTGame::Field mPreviousStep;
    MCBTreeNode * mTree;
    MCBTreeNode * mCurrent;

    void FindNewStep ( TTTGame::Field & __field, int & __x, int & __y );

public:
    MonteCarloBot ();
    void SetFigure ( int __figure );
    int GetFigure ();
    void MakeMove ( TTTGame::Field & __field );
    void Reset ();
};

#endif
