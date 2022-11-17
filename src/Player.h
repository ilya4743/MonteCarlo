#ifndef PLAYER
#define PLAYER

#include <cstdlib>
#include <iostream>
using namespace std;

#include "TicTacToeGame.h"

class Player
{
public:
    virtual void SetFigure ( int __figure ) = 0;
    virtual int GetFigure () = 0;
    virtual void MakeMove ( TTTGame::Field & __field ) = 0;
    virtual void Reset () = 0;
};

class User : public Player
{
private:
    int mFigure;

public:
    User ():mFigure(0){}
    void SetFigure ( int __figure );
    int GetFigure ();
    void MakeMove ( TTTGame::Field & __field );
    void Reset ();
};

class Bot : public Player
{
private:
    int mFigure;
    bool InterruptEnemy ( TTTGame::Field & __field );
    void MakeRandomMove ( TTTGame::Field & __field );

public:
    Bot ():mFigure(0){}
    void SetFigure ( int __figure );
    int GetFigure ();
    void MakeMove ( TTTGame::Field & __field );
    void Reset ();
};

#endif
