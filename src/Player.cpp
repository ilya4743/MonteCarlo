#include "Player.h"


//void User::SetFigure ( int __figure )
//{
//    this->mFigure = __figure;
//}

//int User::GetFigure ()
//{
//    return this->mFigure;
//}

//int User::MakeMove ( Board & __field )
//{
//    cout << "MAKE A MOVE, PLAYER (x y): ";

//    int x = -1, y = -1;
//    while ( !__field.MakeMove(this->mFigure, x, y ) )
//    {
//        cin >> x >> y;
//    }
//    return
//}

//void User::Reset ()
//{
//    // nothing
//}

bool Bot::InterruptEnemy ( Board & __field )
{
    int enemy;
     if ( this->mFigure == CELL::CIRCLE )
        enemy = CELL::CROSS;
    else
        enemy = CELL::CIRCLE;

     //горизонталь
    int c, jj;
    bool b;
    for(int i=0; i<__field.getSize(); i++)
    {
        c=0;
        b=false;
        for(int j=0; j<__field.getSize(); j++)
        {
            if(__field.map[i][j]!=enemy)
            {
                if(__field.map[i][j]==CELL::EMPTY)
                {
                    c++;
                    jj=j;
                }
                else
                {
                    b=true;
                }
            }
        }
        if (c==1 && !b)
        {
            __field.MakeMove(this->mFigure, jj, i );
            return true;
        }
    }

    //вертикаль
    for(int i=0; i<__field.getSize(); i++)
    {
        c=0;
        b=false;
        for(int j=0; j<__field.getSize(); j++)
        {
            if(__field.map[j][i]!=enemy)
            {
                if(__field.map[j][i]==CELL::EMPTY)
                {
                    c++;
                    jj=j;
                }
                else
                {
                    b=true;
                }
            }
        }
        if (c==1 && !b)
        {
            __field.MakeMove(this->mFigure, i, jj );
            return true;
        }
    }

    //диагональ главная
    int t;
    b=false;
    c=0;
    for(int i=0; i<__field.getSize(); i++)
    {
        for(int j=i; j<i+1; j++)
        {
            if(__field.map[i][j]!=enemy)
            {
                if(__field.map[i][j]==CELL::EMPTY)
                {
                    c++;
                    jj=j;
                    t=i;
                }
                else
                {
                    b=true;
                }
            }
        }
    }
    if (c==1 && !b)
    {
        __field.MakeMove(this->mFigure, jj, t );
        return true;
    }

    //диагональ побочная
    b=false;
    c=0;
    for(int i=0; i<__field.getSize(); i++)
    {
        for(int j=__field.getSize()-1-i; j>=0; j--)
        {
            if(__field.map[i][j]!=enemy)
            {
                if(__field.map[i][j]==CELL::EMPTY)
                {
                    c++;
                    jj=j;
                    t=i;
                }
                else
                {
                    b=true;
                }
            }
            break;
        }
    }
    if (c==1 && !b)
    {
        __field.MakeMove(this->mFigure, jj, t );
        return true;
    }
    return false;
}

int Bot::MakeRandomMove ( Board & __field )
{
    int x = -1, y = -1;
    while ( !__field.MakeMove(this->mFigure, x, y) )
    {
        x = rand () % __field.getSize();
        y = rand () % __field.getSize();
    }
    return x+y*__field.getSize();
}

void Bot::SetFigure ( int __figure )
{
    this->mFigure = __figure;
}

int Bot::GetFigure ()
{
    return this->mFigure;
}

int Bot::MakeMove ( Board & __field )
{
    cout << "BOT MAKING A MOVE..." << endl;

    if ( !this->InterruptEnemy ( __field ) )
        this->MakeRandomMove ( __field );
}

void Bot::Reset ()
{
    // nothing
}
