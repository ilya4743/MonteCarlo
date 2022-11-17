#include "Player.h"


void User::SetFigure ( int __figure )
{
    this->mFigure = __figure;
}

int User::GetFigure ()
{
    return this->mFigure;
}

void User::MakeMove ( TTTGame::Field & __field )
{
    cout << "MAKE A MOVE, PLAYER (x y): ";

    int x = -1, y = -1;
    while ( !TTTGame::MakeMove ( __field, this->mFigure, x, y ) )
    {
        cin >> x >> y;
    }
}

void User::Reset ()
{
    // nothing
}

bool Bot::InterruptEnemy ( TTTGame::Field & __field )
{
    int enemy;
     if ( this->mFigure == TTT_CIRCLE )
        enemy = TTT_CROSS;
    else
        enemy = TTT_CIRCLE;

    // horizontal
    for ( int i = 0; i < TTT_FIELDSIZE; i++ )
    {
        if ( __field[i][0] == enemy && __field[i][1] == enemy && __field[i][2] == TTT_EMPTY )
        {
            TTTGame::MakeMove ( __field, this->mFigure, 2, i );
            return true;
        }
        if ( __field[i][0] == enemy && __field[i][2] == enemy && __field[i][1] == TTT_EMPTY )
        {
            TTTGame::MakeMove ( __field, this->mFigure, 1, i );
            return true;
        }
        if ( __field[i][1] == enemy && __field[i][2] == enemy && __field[i][0] == TTT_EMPTY )
        {
            TTTGame::MakeMove ( __field, this->mFigure, 0, i );
            return true;
        }
    }

    // vertical
    for ( int i = 0; i < TTT_FIELDSIZE; i++ )
    {
        if ( __field[0][i] == enemy && __field[1][i] == enemy && __field[2][i] == TTT_EMPTY )
        {
            TTTGame::MakeMove ( __field, this->mFigure, i, 2 );
            return true;
        }
        if ( __field[0][i] == enemy && __field[2][i] == enemy && __field[1][i] == TTT_EMPTY )
        {
            TTTGame::MakeMove ( __field, this->mFigure, i, 1 );
            return true;
        }
        if ( __field[1][i] == enemy && __field[2][i] == enemy && __field[0][i] == TTT_EMPTY )
        {
            TTTGame::MakeMove ( __field, this->mFigure, i, 0 );
            return true;
        }
    }

    // diagonal 1
    int diagonal1[TTT_FIELDSIZE];
    for ( int i = 0; i < TTT_FIELDSIZE; i++ )
        diagonal1[i] = __field[i][i];

    if ( diagonal1[0] == enemy && diagonal1[1] == enemy && diagonal1[2] == TTT_EMPTY )
    {
        while ( !TTTGame::MakeMove ( __field, this->mFigure, 2, 2 ) );
        return true;
    }
    if ( diagonal1[0] == enemy && diagonal1[2] == enemy && diagonal1[1] == TTT_EMPTY )
    {
        while ( !TTTGame::MakeMove ( __field, this->mFigure, 1, 1 ) );
        return true;
    }
    if ( diagonal1[1] == enemy && diagonal1[2] == enemy && diagonal1[0] == TTT_EMPTY )
    {
        while ( !TTTGame::MakeMove ( __field, this->mFigure, 0, 0 ) );
        return true;
    }

    // diagonal 2
    int diagonal2[TTT_FIELDSIZE] = { __field[0][2], __field[1][1], __field[2][0] };

    if ( diagonal2[0] == enemy && diagonal2[1] == enemy && diagonal2[2] == TTT_EMPTY )
    {
        while ( !TTTGame::MakeMove ( __field, this->mFigure, 0, 2 ) );
        return true;
    }
    if ( diagonal2[0] == enemy && diagonal2[2] == enemy && diagonal2[1] == TTT_EMPTY )
    {
        while ( !TTTGame::MakeMove ( __field, this->mFigure, 1, 1 ) );
        return true;
    }
    if ( diagonal2[1] == enemy && diagonal2[2] == enemy && diagonal2[0] == TTT_EMPTY )
    {
        while ( !TTTGame::MakeMove ( __field, this->mFigure, 2, 0 ) );
        return true;
    }

    return false;
}

void Bot::MakeRandomMove ( TTTGame::Field & __field )
{
    int x = -1, y = -1;
    while ( !TTTGame::MakeMove ( __field, this->mFigure, x, y ) )
    {
        x = rand () % TTT_FIELDSIZE;
        y = rand () % TTT_FIELDSIZE;
    }

    // old
    /*for ( int y = 0; y < TTT_FIELDSIZE; y++ )
        for ( int x = 0; x < TTT_FIELDSIZE; x++ )
            if ( __field[y][x] == TTT_EMPTY )
            {
                TTTGame::MakeMove ( __field, this->mFigure, x, y );
                return;
            }*/
}

void Bot::SetFigure ( int __figure )
{
    this->mFigure = __figure;
}

int Bot::GetFigure ()
{
    return this->mFigure;
}

void Bot::MakeMove ( TTTGame::Field & __field )
{
    cout << "BOT MAKING A MOVE..." << endl;

    if ( !this->InterruptEnemy ( __field ) )
        this->MakeRandomMove ( __field );
}

void Bot::Reset ()
{
    // nothing
}
