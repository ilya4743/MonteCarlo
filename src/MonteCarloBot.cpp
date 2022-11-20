#include "MonteCarloBot.h"

void MonteCarloBot::FindNewStep ( Board & __field, int & __x, int & __y )
{
    for (int y = 0; y < __field.getSize(); y++)
        for (int x = 0; x <  __field.getSize(); x++)
            if ( __field.map[y][x] != this->mPreviousStep.map[y][x] )
            {
                __x = x;
                __y = y;
            }
    this->mPreviousStep=__field;
}

MonteCarloBot::MonteCarloBot (int size):mFigure(0),mPreviousStep(size)
{
    this->mTree = new MCBTreeNode;
    this->mCurrent = this->mTree;
}

void MonteCarloBot::SetFigure ( int __figure )
{
    this->mFigure = __figure;
}

int MonteCarloBot::GetFigure ()
{
    return this->mFigure;
}

int MonteCarloBot::MakeMove ( Board & __field )
{
    cout << "MONTE-CARLO BOT MAKING MOVE..." << endl;

    // 0. add node with new move.
    bool exist = false;

    int enemyx = -1, enemyy = -1;
    this->FindNewStep ( __field, enemyx, enemyy );

    for ( MCBTreeNode * node : this->mCurrent->Nodes )
    {
        if ( node->MoveX == enemyx && node->MoveY == enemyy )
        {
            exist = true;
            this->mCurrent = node;
        }
    }

    if ( !exist )
    {
        MCBTreeNode * enemymove = new MCBTreeNode;
        enemymove->Parent = this->mCurrent;
        enemymove->MoveX = enemyx;
        enemymove->MoveY = enemyy;
        enemymove->Player = (this->mFigure == CELL::CROSS) ? CELL::CIRCLE : CELL::CROSS;
        this->mCurrent->Nodes.push_back ( enemymove );
        this->mCurrent = enemymove;
    }

    // 1. selection
    // select node with more wins.
    MCBTreeNode * bestnode = this->mCurrent;
    for ( MCBTreeNode * node : this->mCurrent->Nodes )
    {
        if ( ((double) node->Wins / node->Attempts) > ((double) bestnode->Wins / bestnode->Attempts) )
            bestnode = node;
    }

    // 2. expanding
    // create new node.
    MCBTreeNode * newnode = new MCBTreeNode;
    newnode->Parent = bestnode;
    newnode->Player = this->mFigure;
    this->mCurrent->Nodes.push_back ( newnode );

    // 3. simulation
    // simulate game.
    Board field(__field);

    Player * bot1 = new Bot ();
    bot1->SetFigure ( (this->mFigure == CELL::CROSS) ? CELL::CIRCLE : CELL::CROSS );
    Player * bot2 = new Bot ();
    bot2->SetFigure ( this->mFigure );

    Player * current = bot2;

    while ( field.IsPlayable() )
    {
        current->MakeMove ( field );

        if ( newnode->MoveX == -1 && newnode->MoveY == -1 )
            this->FindNewStep ( field, newnode->MoveX, newnode->MoveY );

        if ( current == bot1 )
            current = bot2;
        else
            current = bot1;
    }

    // 4. backpropagation.

    int winner = field.CheckWin();

    MCBTreeNode * currentnode = newnode;
    while ( currentnode != nullptr )
    {
        currentnode->Attempts++;

        if ( currentnode->Player == winner )
            currentnode->Wins++;

        currentnode = currentnode->Parent;
    }

    // make move...
    this->mCurrent = newnode;
    __field.MakeMove(this->mFigure, mCurrent->MoveX, mCurrent->MoveY );
    return mCurrent->MoveX+mCurrent->MoveY*__field.getSize();
}

void MonteCarloBot::Reset ()
{
    this->mCurrent = this->mTree;
    this->mPreviousStep.Init();
}
