
/** @file mainwindow.cpp
    @author Kevin Kim
    @date May 28, 2015
    @brief MainWindow window constructor defintion.
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lcdnumber.h"
#include "instructions.h"

/** MainWindow window constructor
    @param
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ///Set's the backgroun image of the MainWindow option to Marshawn Skittle Conference
    this->setStyleSheet("background-image:url(:/images/marshawn-lynch-skittles-press-conference.png)");
    this->resize(400, this->height());
    this->resize(600, this->width());

    ///Initialize specific Title Font
    QFont title_font( "Helvetica", 44, QFont::Bold);
        title_font.setItalic(true);
    welcome = new QLabel("Marshawn's Skittle Crusher");
        welcome->setFont(title_font);
        welcome->setStyleSheet("QLabel {color : white; }");
        welcome->setAttribute(Qt::WA_TranslucentBackground);
    QHBoxLayout* welcome_layout = new QHBoxLayout;
        welcome_layout->addWidget(welcome);
        welcome_layout->setAlignment(welcome, Qt::AlignHCenter);

    ///Easy/Hard Buttons
    easy_button = new QPushButton("Easy");
        easy_button->setStyleSheet("QPushButton { background-color:red; color:white; border-style: outset; border-width: 2px; border-color: white}");
        QObject::connect(easy_button, SIGNAL(clicked()), this, SLOT(easy_game_begin()));
    hard_button = new QPushButton("Hard");
        hard_button->setStyleSheet("QPushButton { background-color:red; color:white; border-style: outset; border-width: 2px; border-color: white}");
        QObject::connect(hard_button, SIGNAL(clicked()), this, SLOT(hard_game_begin()));
    Easy_Hard_layout = new QHBoxLayout;
        Easy_Hard_layout->addWidget(easy_button);
        Easy_Hard_layout->addWidget(hard_button);

    ///Instruction Button
    instruction_button = new QPushButton("Instructions");
        instruction_button->setStyleSheet("QPushButton { background-color:red; color:white; border-style: outset; border-width: 2px; border-color: white}");

    ///Final Vertical Layout to put
    final_layout = new QVBoxLayout;
        final_layout->addLayout(welcome_layout);
        final_layout->setAlignment(welcome_layout, Qt::AlignTop);
        final_layout->addLayout(Easy_Hard_layout);
        final_layout->addWidget(instruction_button);

    central = new QWidget;
        central->setLayout(final_layout);

    this->setCentralWidget(central);
}
/**
 Easy Game Begin Function - slot

 @param
 @return
  @brief connects to easy_button. Initializes a 10x10 gameboard with 1:00 on the timer and set's the GameOver to the GameBoard
 */
void MainWindow::easy_game_begin() {
    GameBoard = new gameboard(this,10, 1);
    gameover* go = new gameover;

    GameBoard->setGameOverWindow(go);
    go->setGameboard(GameBoard);
    go->setMainWindow(this);
    this->setCentralWidget(GameBoard);
    this->setStyleSheet("background-color: red;");
}
/**
 Hard Game Begin Function - slot

 @param
 @return
 @brief connects to hard_button. Initializes a 15x15 gameboard with 2:00 on the timer and set's the GameOver to the GameBoard
 */
void MainWindow::hard_game_begin() {
    GameBoard = new gameboard(this,15, 2);
    gameover* go = new gameover;

    GameBoard->setGameOverWindow(go);
    go->setGameboard(GameBoard);
    go->setMainWindow(this);
    this->setCentralWidget(GameBoard);
    this->setStyleSheet("background-color: red;");
}
/**
 Restart Game Function
 @param
 @brief set's the MainWindow to the gameboard object
 *  Color of the board is set to red here
 */
void MainWindow::restart(){
    ///Deletes the gameboard that was just played with
    if(GameBoard->getBoard_Size()==15){
        delete GameBoard;
        ///Allocate a new gameboard on mainwindow
        GameBoard = new gameboard(this,15, 2);
        gameover* go = new gameover;
        GameBoard->setGameOverWindow(go);
        go->setGameboard(GameBoard);
        go->setMainWindow(this);
        this->setCentralWidget(GameBoard);
        this->setStyleSheet("background-color: red;");
    }
    if(GameBoard->getBoard_Size()==10){
        delete GameBoard;
        ///Allocate a new gameboard on mainwindow
        GameBoard = new gameboard(this,10, 1);
        gameover* go = new gameover;
        GameBoard->setGameOverWindow(go);
        go->setGameboard(GameBoard);
        go->setMainWindow(this);
        this->setCentralWidget(GameBoard);
        this->setStyleSheet("background-color: red;");
    }
}

/**
 Set Instructions Window - Slot
 @param instructions* i
 @brief When instruction_button is clicked, instruction window pops up.
 */
void MainWindow::setInstructionsWindow(instructions* i){
    instruction_object = i;
    QObject::connect(instruction_button, SIGNAL(clicked()), instruction_object, SLOT(show()));
    return;
}


void MainWindow::setGameOver(gameover* go){
    gameOver_object = go;
    return;
}

/**
 MainWindow Destructor
 */
MainWindow::~MainWindow()
{

}
