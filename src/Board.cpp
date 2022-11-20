#include "Board.h"

void Board::print()
{
    for ( int i = 0; i < this->size; i++ )
    {
        for ( int j = 0; j < this->size; j++ )
        {
            if ( j != 0 )
                cout << '|';

            cout << ' ' << this->map[i][j] << ' ';
        }
        cout<<endl;
    }
}

bool Board::MakeMove (int __who, int __wherex, int __wherey)
{
    if ( __wherex < 0 || __wherex >= this->size )
        return false;
    if ( __wherey < 0 || __wherey >= this->size )
        return false;

    if ( map[__wherey][__wherex] != CELL::EMPTY )
        return false;

    map[__wherey][__wherex] = __who;
    return true;
}

int Board::CheckWin ()
{
    //горизонталь
   bool b;
   for(int i=0; i<this->size; i++)
   {
       b=false;
       for(int j=1; j<this->size; j++)
       {
           if(map[i][j-1]==map[i][j]&&map[i][j]!=CELL::EMPTY)
              b=true;
           else
           {
               b=false;
               break;
           }

       }
       if (b)
           return map[i][0];
   }

   //вертикаль
   for(int i=0; i<this->size; i++)
   {
       b=false;
       for(int j=1; j<this->size; j++)
       {
            if(map[j-1][i]==map[j][i]&&map[j][i]!=CELL::EMPTY)
                b=true;
            else
            {
                b=false;
                break;
            }

       }
       if (b)
           return map[0][i];
   }

   //диагональ главная
   b=false;
   for(int i=1; i<this->size; i++)
        if(map[i-1][i-1]==map[i][i]&&map[i][i]!=CELL::EMPTY)
            b=true;
        else
        {
            b=false;
            break;
        }

   if (b)
       return map[0][0];

   //диагональ побочная
   b=false;
   for(int i=1; i<this->size; i++)
        if(map[i-1][this->size-i]==map[i][this->size-(i+1)]&&map[i][this->size-(i+1)]!=CELL::EMPTY)
            b=true;
        else
        {
            b=false;
            break;
        }

   if (b)
       return map[this->size-1][0];

    /// no one wins
    return CELL::EMPTY;
}

bool Board::IsPlayable()
{
    if ( CheckWin () ) return false;

    for ( int i = 0; i < this->size; i++ )
        for ( int j = 0; j < this->size; j++ )
            if ( map[i][j] == CELL::EMPTY )
                return true;

    return false;
}

void Board::Init()
{
    for ( int i = 0; i < size; i++ )
        for ( int j = 0; j < size; j++ )
            map[i][j] = CELL::EMPTY;
}

void Board::Init(int size)
{
    for ( int i = 0; i < size; i++ )
        for ( int j = 0; j < size; j++ )
            map[i][j] = CELL::EMPTY;
}

bool Board::setPlayerInput(size_t row, size_t col, CELL currentPlayer)
{
    // The game is over, so no input is allowed untill game resets.
    if (BoardState::NoWinner != CheckWin())
        return false;

    // Row input is not valid.
    if (row >= size)
        throw std::out_of_range("Row index is out of range.");

    // Column input is not valid.
    if (col >= size)
        throw std::out_of_range("Column index is out of range.");

    // Cell is not empty.
    if (CELL::EMPTY != map[row][col])
        return false;

    // Update cell with current player's mark.
    map[row][col] = currentPlayer;

    return true;
}
