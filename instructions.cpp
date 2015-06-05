/** @file instructions.cpp
    @author Kevin Kim
    @date May 28, 2015
    @brief This is the source file for the Instructions class.
    This file contains the constructor for the instruction window object that portrays the rules on how to play this game.
    Also the destructor.
*/
#include "instructions.h"


/**
   Instruction Constructor
 */
instructions::instructions(QWidget *parent) :
    QWidget(parent)
{
    setStyleSheet("background-color:red; color : white; font-weight: bold");

    /************** Setting up fonts **************/

    QFont* skittle_font=new QFont("Helvetica");
        skittle_font->setItalic(true);
        skittle_font->setPixelSize(96);
    QFont s("Helvetica");
    QFont f( "Verdana", 12);
    QFont t( "Verdana", 24, QFont::Bold);

    /************** Title that says "Instructions" **************/
    QLabel* title = new QLabel ("Instructions");
    title->setFont(t);

    /************** Welcome **************/
    QLabel* welcome = new QLabel("Help Marshawn crush skittles! The goal of this game is to achieve the highest number of points by crushing skittles in a limited amount of time.");
    welcome->setWordWrap(true);
    welcome->setFont(f);

    /************** Diagram showing game pieces **************/
    QPixmap* marshawn_lynch = new QPixmap(":/images/Marshawn Lynch BoardPiece.jpeg");
    QPixmap* red_skittle = new QPixmap(":/images/Red Skittle.gif");
    QPixmap* orange_skittle = new QPixmap(":/images/Orange Skittle.gif");
    QPixmap* yellow_skittle = new QPixmap(":/images/Yellow Skittle.gif");
    QPixmap* green_skittle = new QPixmap(":/images/Green Skittle.gif");
    QPixmap* purple_skittle = new QPixmap(":/images/Purple Skittle.gif");

    QLabel* m=new QLabel;
        m->setPixmap(*marshawn_lynch);
        m->setScaledContents(true);
        m->setFixedSize(50,50);
    QLabel* r=new QLabel;
        r->setPixmap(*red_skittle);
        r->setScaledContents(true);
        r->setFixedSize(30,30);
    QLabel* o=new QLabel;
        o->setPixmap(*orange_skittle);
        o->setScaledContents(true);
        o->setFixedSize(30,30);
    QLabel* y=new QLabel;
        y->setPixmap(*yellow_skittle);
        y->setScaledContents(true);
        y->setFixedSize(30,30);
    QLabel* g=new QLabel;
        g->setPixmap(*green_skittle);
        g->setScaledContents(true);
        g->setFixedSize(30,30);
    QLabel* p=new QLabel;
        p->setPixmap(*purple_skittle);
        p->setScaledContents(true);
        p->setFixedSize(30,30);

    QHBoxLayout* game_piece_diagrams = new QHBoxLayout;
    QSpacerItem* horizontal_space = new QSpacerItem(100,10);
        game_piece_diagrams->addWidget(m);
        game_piece_diagrams->addSpacerItem(horizontal_space);
        game_piece_diagrams->addWidget(r);
        game_piece_diagrams->addWidget(o);
        game_piece_diagrams->addWidget(y);
        game_piece_diagrams->addWidget(g);
        game_piece_diagrams->addWidget(p);

    /************** basic rules **************/
    ///
    QLabel* basic_rules = new QLabel("Move Marshawn to an empty spot and press the spacebar\n"
                                     "If two or more skittles\n"
                                     "1) are the same color\n"
                                     "2) and are along Marshawn's vertical and horizontal axis\n"
                                     "Marshawn will crush the skittles! When you crush skittles, they diassappear and you get points!");
        basic_rules->setWordWrap(true);

    /************** EXAMPLE **************/
    QLabel* example = new QLabel("Example:\n"
                                 "Move Marshawn to the green star and press the spacebar to crush the top and bottom green skittles and left and right purple skittles (Crush 4 skittles)\n"
                                 "Move Marshawn to the purple star and press spacebar to crush the left, right, and bottom purple skittles (Crush 3 skittles)");
    QPixmap* example_diagram = new QPixmap(":/images/Marshawn's Skittle Crusher - EXAMPLE.png");
    QLabel* example_pic=new QLabel;
    example_pic->setPixmap(*example_diagram);
    example_pic->setScaledContents(true);
    example_pic->setFixedSize(215,200);
    //example_pic->setAlignment(Qt::AlignCenter);

    /************** Point System/Easy and Hard **************/
    QLabel* point_system = new QLabel("POINT SYSTEM:                                                       LOSS OF LIFE:\n"
                                      "2 Skittle Crush x 1 multiplier = 2 Points                  You lose a life when you crush skittles when:\n"
                                      "3 Skittle Crush x 2 multiplier = 6 Points                  1) Marshawn is on a space with skittles on it\n"
                                      "4 Skittle Crush x 3 multiplier = 12 Points                2) or you do an invalid crush aka none of the skittles match along Marshawn's vertical and horizontal axis\n"
                                      "\n"
                                      "Easy Mode = 1:00 minutes and small gameboard\n"
                                      "Hard Mode = 2:00 minutes and big gameboard");

    /************** Conclusion **************/
    QLabel* conclusion = new QLabel("You are now ready to crush some skittles. Let's go Beast Mode!");

    /************** final instruction layout **************/

    QVBoxLayout* instruction_layout = new QVBoxLayout;
        instruction_layout->addWidget(title);
        instruction_layout->addWidget(welcome);
        instruction_layout->addLayout(game_piece_diagrams);
        instruction_layout->addWidget(basic_rules);
        instruction_layout->addWidget(example);
        instruction_layout->addWidget(example_pic);
        instruction_layout->setAlignment(example_pic,Qt::AlignCenter);
        instruction_layout->addWidget(point_system);
        instruction_layout->addWidget(conclusion);

    setLayout(instruction_layout);

}

instructions::~instructions()
{

}
