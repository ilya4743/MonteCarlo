#ifndef MONTECARLOBOT
#define MONTECARLOBOT

#include <iostream>
#include <vector>
using namespace std;

#include "Player.h"
#include "Board.h"
#include "defs.h"

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
    Board mPreviousStep;
    MCBTreeNode * mTree;
    MCBTreeNode * mCurrent;

    void FindNewStep ( Board & __field, int & __x, int & __y );

public:
    MonteCarloBot (int size);
    void SetFigure ( int __figure );
    int GetFigure ();
    int MakeMove ( Board & __field );
    void Reset ();
};

#endif
