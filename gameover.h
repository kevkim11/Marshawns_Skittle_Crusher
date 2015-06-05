/** @file gameover.h
    @author Kevin Kim
    @date May 28, 2015
    @brief This is a header file for the gameover class.
    This file contains the list of functions and variable used in gameover.
    The gameover class is evoked when the player loses all of his life or the time runs out.
    This class allows players to play again or end game.
*/

#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include "mainwindow.h"
#include "gameboard.h"

class gameboard;
class MainWindow;

/**
  @class gameover
  @brief The gameover class is evoked when the player loses all of his life or the time runs out.
 */
class gameover : public QWidget
{
public:
    explicit gameover(QWidget *parent = 0);
    void setGameboard(gameboard* b);
    void setMainWindow(MainWindow* mw);
    ~gameover();
private:
    QPushButton* retry_button;
    QPushButton* no_button;
    gameboard* board;
    MainWindow* mainwindow;
};

#endif // GAMEOVER_H
