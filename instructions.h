/** @file instructions.h
    @author Kevin Kim
    @date May 28, 2015
    @brief This is a header file for the instructions class.
        Creates a Window that shows the Instructions on how to play the game.
*/
#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPixmap>

class MainWindow;

class instructions : public QWidget
{
    Q_OBJECT

public:
    explicit instructions(QWidget *parent = 0);
    ~instructions();

private:
    MainWindow* mw;
};

#endif // INSTRUCTIONS_H
