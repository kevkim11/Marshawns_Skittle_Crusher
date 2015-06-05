/** @file mainwindow.h
    @author Kevin Kim
    @date May 28, 2015
    @brief This is a header file for the MainWindow class.

*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "lcdnumber.h"
#include "gameboard.h"
#include "instructions.h"
#include "gameover.h"
#include <QPixmap>

class gameboard;
class instructions;
class gameover;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void easy_game_begin();
    void hard_game_begin();

    void restart();

    void setInstructionsWindow(instructions* i);
    void setGameOver(gameover* go);

public:
    explicit MainWindow(QWidget *parent = 0);
    QPushButton* start_button;
    QPushButton* hard_button;
    QPushButton* easy_button;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    gameboard* GameBoard;

    QButtonGroup* buttonGroup;
    QVBoxLayout* final_layout;
    QHBoxLayout* Easy_Hard_layout;
    QLabel* welcome;

    QPixmap* welcome_picture;

    instructions* instruction_object;
    QPushButton* instruction_button;

    gameover* gameOver_object;

    QWidget* central;
};

#endif // MAINWINDOW_H
