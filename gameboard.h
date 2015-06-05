/** @file gameboard.h
    @author Kevin Kim
    @date
    @brief This is a header file for the gameboard class.
    This file contains the list of functions and variable used in gameboard.
    This gameboard is where the game is played.
*/

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <chrono>
#include <random>
#include <iostream>
#include <QTimer>
#include <QKeyEvent>
#include <QHBoxLayout>
#include "lcdnumber.h"
#include "mainwindow.h"
#include <QKeyEvent>
#include <QSpacerItem>
#include "instructions.h"
#include <QString>
#include <QPixmap>
#include "gameover.h"
#include <QPushButton>

class LCDNumber;
class gameover;

namespace Ui {
class gameboard;
}

class gameboard : public QWidget
{
    Q_OBJECT
signals:
    void game_over();

public slots:
    void startGame();
    void gamedone();

public:
    explicit gameboard(QWidget *parent = 0, size_t board_sz = 15, int min = 2);

    void setGameOverWindow(gameover* go);
    ///Window Objects
    gameover* gameOver_object;

    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent *e);

    size_t getBoard_Size(){return board_size;};

    ~gameboard();

private:
    bool game_is_over=false;

    ///Board Variables - board_size, minutes on timer
    size_t board_size;
    int minute;

    /** Board features */
    QWidget* board;
    QLabel** labels;
    int* values;

    /// Top bar variables
    QLabel* lives_left_value;
    QWidget* Top;
    int lives_remaining;
    QLabel** lives;
    /// Bottom bar variables
    QWidget* Bottom;
    ///Timer
    QLabel* timer;
    LCDNumber *clock;
    ///Score
    QLabel* score_lcd;
    int points = 0;
    ///Crunch Output
    QLabel* crush_output;
    QString type_of_crush;

    ///Marshawn Lynch Piece
    const QPixmap* marshawns_image;
    QPoint *marshawns_position;

    ///Game Logic Functions
    bool crushSkittles();
    bool crushSkittles(int x, int y);
    void updateAfterCrush(bool flag, int& left, int& right, int& up, int& down, QLabel* left_label, QLabel* right_label, QLabel* up_label, QLabel* down_label);
    bool isValidCrush(int x, int y, int left, int right,int up, int down);
    void updateMarshawn(int px, int py, int nx, int ny);

    ///Skittles
    QPixmap* red_skittle;
    QPixmap* orange_skittle;
    QPixmap* yellow_skittle;
    QPixmap* green_skittle;
    QPixmap* purple_skittle;
    ///This is the dummy skittle that will be randomly assigned to one of the colored skittles
    QPixmap* random_skittle;

    ///updateMarshawn function
    QLabel* current_under;
    QLabel* next_under;

    //Ui::gameboard *ui;
};
#endif // GAMEBOARD_H
