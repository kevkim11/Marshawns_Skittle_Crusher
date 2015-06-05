/** @file gameover.cpp
    @author Kevin Kim
    @date May 28, 2015
    @brief This is a source file for the gameover class.
    This file contains the list of functions and variable used in gameover.
    The gameover class is evoked when the player loses all of his life or the time runs out.
    This class allows players to play again or end game.
*/
#include "gameover.h"

gameover::gameover(QWidget *parent):
    QWidget(parent)
{
    QFont helvetica_italisized_font( "Helvetica", 44, QFont::Bold);
        helvetica_italisized_font.setItalic(true);
    this->setStyleSheet("background-image:url(:/images/GameOverPic.jpg)");
    setFixedSize(500,300);

    /************** Title that says "Game Over" **************/
    QLabel* title = new QLabel ("Game Over!");
        title->setFont(helvetica_italisized_font);
        title->setStyleSheet("QLabel {color : white; }");
        title->setAttribute(Qt::WA_TranslucentBackground);
    QHBoxLayout* title_layout = new QHBoxLayout;
        title_layout->addWidget(title);
        title_layout->setAlignment(title, Qt::AlignHCenter);

    ///CONVERTING INTS->QSTRING TO PORTRAY POINTS
//    std::string s = std::to_string(42);
//    QLabel* score = new QLabel;

    /************** Buttons **************/
    QHBoxLayout* buttons =  new QHBoxLayout();
    retry_button = new QPushButton("Retry");
        retry_button->setStyleSheet("QPushButton { background-color:red; color:white; border-style: outset; border-width: 2px; border-color: white}");

    no_button = new QPushButton("Quit");
        no_button->setStyleSheet("QPushButton { background-color:red; color:white; border-style: outset; border-width: 2px; border-color: white}");
    buttons->addWidget(retry_button);
    buttons->addWidget(no_button);

    QVBoxLayout* overall = new QVBoxLayout;
        overall->addLayout(title_layout);
        overall->setAlignment(title_layout, Qt::AlignTop);
        overall->addLayout(buttons);
    setLayout(overall);
}
///@param gameboard
void gameover::setGameboard(gameboard* b){
    board = b;
    ///Closes the GameOver Window when the retry button is clicked
    QObject::connect(retry_button,SIGNAL(clicked()), this,SLOT(close()));
}
///@param MainWindow
void gameover::setMainWindow(MainWindow* mw){
    mainwindow = mw;
    ///Closes the MainWindow aka the Gameboard when the no/quit button is clicked
    QObject::connect(no_button,SIGNAL(clicked()), mainwindow,SLOT(close()));
    ///Closes the gameover window when no/quit button is clicked
    QObject::connect(no_button,SIGNAL(clicked()), this,SLOT(close()));
    ///Retry
    QObject::connect(retry_button,SIGNAL(clicked()), mainwindow,SLOT(restart()));
}

gameover::~gameover()
{

}

