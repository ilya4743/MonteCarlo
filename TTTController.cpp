#include "TTTController.h"
#include "TicTacToeGame1.h"
#include <QPushButton>

TTTController::TTTController(const TTTOptions &options, QObject *parent)
    : QObject(parent),
      view_(),
      board(options.boardSize),
      options_(options),
      currentPlayer_(CELL::CROSS)
{
    // Build GUI
    cells_ = view_.buildCellButtons(options.boardSize);

    // Set Connections to the UI elements.
    setConnections();

    player1 = new Bot ();
    player1->SetFigure ( CELL::CROSS );
    player2 = new MonteCarloBot (board.getSize());
    player2->SetFigure ( CELL::CIRCLE );

    Player * current = player1;

    for (int i = 0; i < board.getSize()*board.getSize(); i++ )
    {
        while ( board.IsPlayable () )
        {
            current->MakeMove ( board );

            if ( current == player1 )
                current = player2;
            else
                current = player1;
        }

        player1->Reset ();
        player2->Reset ();
        board.Init();
    }
    delete player1;


    // Setup a new game.
    reset();
}

void TTTController::startGame()
{
    // Shows the gameplay GUI.
    view_.exec();
}

void TTTController::setConnections()
{
    // Cell connections.
    for (Cell &cell : cells_)
        connect(cell.cellBtn, &QPushButton::clicked, [&] { updateGame(cell); });

    // New Game Connection - resetting the game.
    connect(&view_, &TicTacToeGame::newGame, this, [&] { reset(); });

    // Connect AI to play after a cell is chosen by human input.
    connect(this, &TTTController::turnFinished, [=] { AIAgentPlay(); });
}

void TTTController::updateGameState(Cell &cell)
{
    // Updates the cell view.
    this->view_.updateCell(cell, currentPlayer_);

    // Update board state and declare state if its a final state.
    int boardState = board.CheckWin();
    if (BoardState::NoWinner != boardState)
        view_.declareGameState(BoardState(boardState));

    // Switch the players.
    switchPlayer();
}

void TTTController::reset()
{
    // Resets the current player back to X.
    currentPlayer_ = CELL::CROSS;
    // Resets the View GUI elements.
    view_.reset(cells_);
    // Resets the internal Representation of the board.
    board.Init();
}

void TTTController::AIAgentPlay()
{
    if(board.IsPlayable())
    {
        int cellIdx = player2->MakeMove(board);
        if (defaults::INVALID_CELL != cellIdx)
            updateGameState(cells_.at(static_cast<size_t>(cellIdx)));
    }
}

void TTTController::switchPlayer()
{
    if (CELL::CROSS == currentPlayer_)
        currentPlayer_ = CELL::CIRCLE;
    else if (CELL::CIRCLE == currentPlayer_)
        currentPlayer_ = CELL::CROSS;
}

void TTTController::updateGame(Cell &cell)
{
    bool success = board.setPlayerInput(static_cast<size_t>(cell.row),
                                         static_cast<size_t>(cell.col),
                                         currentPlayer_);
    if (success) {
        updateGameState(cell);
        emit turnFinished();
    }
}

//void doo(Board& field)
//{
//    {

//        Player * player1 = new Bot ();
//        player1->SetFigure ( CELL::CROSS );
//        Player * player2 = new MonteCarloBot (field.getSize());
//        player2->SetFigure ( CELL::CIRCLE );

//        Player * current = player1;

//        for (int i = 0; i < field.getSize()*field.getSize(); i++ )
//        {
//            while ( field.IsPlayable () )
//            {
//                current->MakeMove ( field );

//                if ( current == player1 )
//                    current = player2;
//                else
//                    current = player1;
//            }

//            player1->Reset ();
//            player2->Reset ();
//            field.Init();
//        }

//        player1 = new User ();
//        player1->SetFigure ( CELL::CROSS );
//        current = player1;

//        while (field.IsPlayable())
//        {
//            current->MakeMove ( field );

//            if ( current == player1 )
//                current = player2;
//            else
//                current = player1;
//        }
//    }
//}
