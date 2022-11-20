#ifndef PLAYER
#define PLAYER

#include <cstdlib>
#include <iostream>
#include "Board.h"
#include "defs.h"

using namespace std;

class Player
{
public:
    virtual void SetFigure ( int __figure ) = 0;
    virtual int GetFigure () = 0;
    virtual int MakeMove ( Board & __field ) = 0;
    virtual void Reset () = 0;
};

//class User : public Player
//{
//private:
//    int mFigure;

//public:
//    User ():mFigure(0){}
//    void SetFigure ( int __figure );
//    int GetFigure ();
//    int MakeMove ( Board & __field );
//    void Reset ();
//};

class Bot : public Player
{
private:
    int mFigure;
    bool InterruptEnemy ( Board & __field );
    int MakeRandomMove ( Board & __field );

public:
    Bot ():mFigure(0){}
    void SetFigure ( int __figure );
    int GetFigure ();
    int MakeMove ( Board & __field );
    void Reset ();
};

#endif
