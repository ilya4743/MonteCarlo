#include <iostream>
using namespace std;

#include "Player.h"
#include "MonteCarloBot.h"
#include "Board.h"
#include "defs.h"

int main ()
{
    Board field(3);
    field.Init();

    Player * player1 = new Bot ();
    //player1->SetFigure ( CELL::CROSS );
    Player * player2 = new MonteCarloBot (3);
    //player2->SetFigure ( CELL::CIRCLE );

    Player * current = player1;

//    cout << "Monte-Carlo bot setting up..." << endl;
//    for (int i = 0; i < field.getSize()*field.getSize(); i++ )
//    {
//        while ( field.IsPlayable () )
//        {
//            current->MakeMove ( field );

//            if ( current == player1 )
//                current = player2;
//            else
//                current = player1;
//        }

//        player1->Reset ();
//        player2->Reset ();
//        field.Init();
//    }

//    system ( "cls" );

    player1 = new User ();
    player1->SetFigure ( CELL::CROSS );
    current = player1;

    while (field.IsPlayable())
    {
        field.print ();

        cout << "Player " << current->GetFigure () << " turn: ";

        current->MakeMove ( field );

        if ( current == player1 )
            current = player2;
        else
            current = player1;
    }

    field.print ();
    cout << "Winner is Player " << field.CheckWin () << endl;
    system ( "pause" );
}
