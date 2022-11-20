#include "TitleScreen.h"
#include "TTTController.h"

TitleScreen::TitleScreen(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TitleScreen)
{
    ui->setupUi(this);
    setConnections();
}

void TitleScreen::setConnections()
{
    connect(ui->boardSize, SIGNAL(valueChanged(int)), SLOT(updateBoardSize(int)));
    connect(ui->startGame, SIGNAL(clicked()), SLOT(startGame()));
}

void TitleScreen::updateBoardSize(int size)
{
    ui->boardSizeValue->setText(QString::number(size));
    options_.boardSize = static_cast<size_t>(size);
}

void TitleScreen::startGame()
{
    this->hide();
    TTTController ttt(options_);
    ttt.startGame();
    this->show();
}

void TitleScreen::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
    emit exited();
}
