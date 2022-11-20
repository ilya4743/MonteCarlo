#ifndef TITLESCREEN_H
#define TITLESCREEN_H
#include "TTTCommonTypes.h"
#include "ui_titlescreen.h"
#include <QMainWindow>
#include <memory>

/**
 * @brief The TitleScreen class is responsible for the GUI of the title screen,
 * its main functionality is to gather game options set by the user,
 * then starting a game by creating a Tic Tac Toe controller with the user options.
 */

class TitleScreen final : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief TitleScreen constructs the view of the title screen.
     * @param parent is a QWidget type parent that owns this instance of the controller.
     */
    explicit TitleScreen(QWidget *parent = nullptr);

private:
    /**
     * @brief ui is a reference to the ui object of the tic tac toe game.
     */
    std::unique_ptr<Ui::TitleScreen> ui;
    /**
     * @brief setConnections sets connections to gather game options from the GUI elements.
     */
    void setConnections();
    /**
     * @brief options are the values and flags that control a tic tac toe game.
     */
    TTTOptions options_;
    /**
     * @brief closeEvent manually handles the closing event defined in the base class QWidget.
     * @param event: the closing event.
     */
    void closeEvent(QCloseEvent *event) override;

public slots:
    /**
     * @brief updateBoardSize updates the board size in the current options.
     * @param size: the number of rows or columns in the board.
     */
    void updateBoardSize(int size);
    /**
     * @brief startGame hides the title screen and creates a Tic tac toe controller to start a game.
     */
    void startGame();


signals:
    /**
     * @brief exited is emitted to manually handle the close functionality.
     */
    void exited();
};

#endif // TITLESCREEN_H
