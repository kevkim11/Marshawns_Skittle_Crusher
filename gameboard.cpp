/** @file gameboard.cpp
    @author Kevin Kim
    @brief This is the main source file for the gameboard class.
    Has the constructor to build a gameboard object. The parent widget is set to mainwindow when the game is started.
*/

#include "gameboard.h"
#include "ui_gameboard.h"

// Random number generator for C++11
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    //std::uniform_int_distribution<int> distribution(0,14); // generates a number from 0 - 14
    std::uniform_int_distribution<int> skittles_colors(1,6);//generates a number from 1 - 6

/** Creates a gameboard object based on the paramenters which are set
    @param parent is the Qwidget object - In this case the parent widget is set to as the MainWindow
    @param timer is the timer object on the board
    @param clock keeps track of time
 */
gameboard::gameboard(QWidget *parent, size_t board_sz, int min) :
    QWidget(parent),board_size(board_sz), minute(min)
{
    setStyleSheet("background-color: red;");
    ///Marshawn Lynch Image Loading
    QString fileName(":/images/Marshawn Lynch BoardPiece.jpeg");
    marshawns_image = new QPixmap(fileName);
    /************** Skittle images **************/
    QString filename_red_skittle(":/images/Red Skittle.gif");
    red_skittle = new QPixmap(filename_red_skittle);

    QString filename_orange_skittle(":/images/Orange Skittle.gif");
    orange_skittle = new QPixmap(filename_orange_skittle);

    QString filename_green_skittle(":/images/Green Skittle.gif");
    green_skittle = new QPixmap(filename_green_skittle);

    QString filename_yellow_skittle(":/images/Yellow Skittle.gif");
    yellow_skittle = new QPixmap(filename_yellow_skittle);

    QString filename_purple_skittle(":/images/Purple Skittle.gif");
    purple_skittle = new QPixmap(filename_purple_skittle);

    /************** Top Bar **************/
    QFont Helvetica_italic( "Helvetica"); Helvetica_italic.setItalic(true);

    Top = new QWidget;
        Top->setStyleSheet("QLabel { background-color:white; "
                                     "color:purple; "
                                      "border-style: outset; "
                                       "border-width:2px; "
                                        "border-color: black }");
    QLabel* life_label = new QLabel("Lives Remaining:");
        life_label->setFont(Helvetica_italic);
    // This code sets up the Top bar
    // This layout will space out the elements above
    QHBoxLayout *top_bar = new QHBoxLayout(Top);
    lives_remaining = 3;
    lives = new QLabel*[lives_remaining];
    top_bar->addWidget(life_label);
    // This line above is important, it is an array of QLabel POINTERS.
    // You have to input heap memory pointers for the memory management system to work properly.
    for(size_t i=0;i<lives_remaining;i++) {
        lives[i] = new QLabel;
        lives[i]->setPixmap(*marshawns_image);
        lives[i]->setMinimumSize(30,30);
        lives[i]->setMaximumSize(30,30);
        lives[i]->setScaledContents(true);
        top_bar->addWidget(lives[i]);
    }

    /************** Game Board Build **************/
    ///create board object for all the widgets to be laid out on
    board = new QWidget;
    labels = new QLabel*[board_size*board_size];
    values = new int[board_size*board_size];
    QGridLayout *SquareGrid = new QGridLayout(board);
        SquareGrid->setGeometry(QRect());
        SquareGrid->setSpacing(0);
    /************** Board Layout **************/
    /// Assigning all the values on the board to be 0
    for(size_t i=0;i<board_size;i++) {
        for(size_t j=0;j<board_size;j++) {
            /// Assigning all the values to 0
            values[i*board_size+j] = 0;
            /// Create label and set properties.
            labels[i*board_size+j] = new QLabel;
            labels[i*board_size+j]->setMinimumSize(30,30);
            labels[i*board_size+j]->setMaximumSize(30,30);
            labels[i*board_size+j]->setStyleSheet("QLabel { background-color : white; color : black; }");
            labels[i*board_size+j]->setFrameStyle(2);
            labels[i*board_size+j]->setAlignment(Qt::AlignCenter);
            ///Each skittle color is assigned to a random number from 1-5. If the number is 6 then no skittle is added onto the gameboard
            int number_color_conversion = skittles_colors(generator);
            if (number_color_conversion<6){
                if (number_color_conversion==1){
                    random_skittle=red_skittle;
                    values[i*board_size+j]=1;
                }
                if (number_color_conversion==2){
                    random_skittle=orange_skittle;
                    values[i*board_size+j]=2;
                }
                if (number_color_conversion==3){
                    random_skittle=yellow_skittle;
                    values[i*board_size+j]=3;
                }
                if (number_color_conversion==4){
                    random_skittle=green_skittle;
                    values[i*board_size+j]=4;
                }
                if (number_color_conversion==5){
                    random_skittle=purple_skittle;
                    values[i*board_size+j]=5;
                }
                labels[i*board_size+j]->setPixmap(*random_skittle);
                labels[i*board_size+j]->setScaledContents(true);
            }
            /// Add label to the layout
            SquareGrid->addWidget(labels[i*board_size+j] ,i,j);
        }
        std::cout << std::endl;
    }

    /// Initialize the marshawn at the top left corner, coordinate (0,0).
    marshawns_position = new QPoint(0,0);

    /************** Timer **************/
    QLabel* time_remaining = new QLabel("Time Remaining:");
        time_remaining->setFont(Helvetica_italic);
    QFont clock_font( "Helvetica", 60, QFont::Bold);
    timer = new QLabel;
    clock = new LCDNumber(timer,minute,00);
        clock->setFixedSize(280, 80);
        clock->setFont(clock_font);
        clock->setAlignment(Qt::AlignCenter);
        clock->start();
        clock->timer->start(1000); // starts the clock.

    /************** Score Board **************/
    QLabel* score_label = new QLabel("Score:");
        score_label->setFont(Helvetica_italic);
    score_lcd = new QLabel;
        score_lcd->setNum(points);
        score_lcd->setFixedSize(280,50);
        score_lcd->setAlignment(Qt::AlignCenter);

    QHBoxLayout* score_layout = new QHBoxLayout;
        score_layout->addWidget(score_label);
        score_layout->addWidget(score_lcd);

    /************** crush_output/multiplier **************/
    QLabel* crush_output_label = new QLabel("Type of Crush:");
        crush_output_label->setFont(Helvetica_italic);
    crush_output = new QLabel;
        crush_output->setText(type_of_crush);
        crush_output->setFixedSize(280,50);
        crush_output->setAlignment(Qt::AlignCenter);
    QHBoxLayout* crush_output_layout = new QHBoxLayout;
        crush_output_layout->addWidget(crush_output_label);
        crush_output_layout->addWidget(crush_output);

    /************** score and crush output **************/
    QVBoxLayout* score_and_multiplier = new QVBoxLayout;
        score_and_multiplier->addLayout(score_layout);
        score_and_multiplier->addLayout(crush_output_layout);

    /************** Bottom **************/
    Bottom = new QWidget;
        Bottom->setStyleSheet("QLabel { background: red; color : white; }");
    QHBoxLayout* bottom_bar = new QHBoxLayout(Bottom);
        bottom_bar->addWidget(time_remaining);
        bottom_bar->addWidget(clock);
        bottom_bar->addLayout(score_and_multiplier);

    /// Create a vertical box layout for the two pieces
    QVBoxLayout* piece_together = new QVBoxLayout;
    piece_together->addWidget(Top,0,Qt::AlignCenter);
    piece_together->addWidget(board,0,Qt::AlignCenter);
    piece_together->addWidget(Bottom,0,Qt::AlignCenter);
    this->setLayout(piece_together);
}
/**
 gameboard destructor
 @brief deallocate the gameboard object and deletes the gameboard object variables
 */
gameboard::~gameboard()
{
    delete [] values;
    delete [] marshawns_position;
}
/**
 keypressevent

 @param
 @return void
 @brief assigns the keyboard keys to Marshawn moving on the board and the space bar is connected to crushSkittles function
 */
void gameboard::keyPressEvent(QKeyEvent *event){

    size_t x = marshawns_position->rx();
    size_t y = marshawns_position->ry();

    switch (event->key()) {
        case Qt::Key_Left:
            if(marshawns_position->rx() != 0)
               updateMarshawn(x,y,x-1,y);
            break;

        case Qt::Key_Right:
            if(marshawns_position->rx() != board_size-1)
               updateMarshawn(x,y,x+1,y);
            break;

        case Qt::Key_Up:
            if(marshawns_position->ry() != 0)
               updateMarshawn(x,y,x,y-1);
            break;
        case Qt::Key_Down:
            if(marshawns_position->ry() != board_size-1)
               updateMarshawn(x,y,x,y+1);
            break;
        case Qt::Key_Space:
            crushSkittles(x,y);
            break;

    default:
        QWidget::keyPressEvent(event);
    }
    game_is_over = false;
    // Need both lines to force a repaint.
    // This line forces processor to process all previously promised events.
    QCoreApplication::processEvents();
    // This one QUEUES up a repaint
    repaint();
    return;
}
/**
 Update Marshawn Function

 @param int previous_x, previous_y
        int next_x, next_y
 @return void
 @brief used to update marshawn after he's been moved/crushed skittles on the board.
 */
void gameboard::updateMarshawn(int previous_x, int previous_y, int next_x, int next_y) {
    ///Clear the label that Marshawn was on first
    labels[previous_y*board_size+previous_x]->clear();
    ///Then whatever values/skittles were placed in the label before, replace it back when Marshawn moves out of the board space
      if(values[previous_y*board_size+previous_x]==1){
          labels[previous_y*board_size+previous_x]->setPixmap(*red_skittle);
          labels[previous_y*board_size+previous_x]->setScaledContents(true);
      }
      if(values[previous_y*board_size+previous_x]==2){
          labels[previous_y*board_size+previous_x]->setPixmap(*orange_skittle);
          labels[previous_y*board_size+previous_x]->setScaledContents(true);
      }
      if(values[previous_y*board_size+previous_x]==3){
          labels[previous_y*board_size+previous_x]->setPixmap(*yellow_skittle);
          labels[previous_y*board_size+previous_x]->setScaledContents(true);
      }
      if(values[previous_y*board_size+previous_x]==4){
          labels[previous_y*board_size+previous_x]->setPixmap(*green_skittle);
          labels[previous_y*board_size+previous_x]->setScaledContents(true);
      }
      if(values[previous_y*board_size+previous_x]==5){
          labels[previous_y*board_size+previous_x]->setPixmap(*purple_skittle);
          labels[previous_y*board_size+previous_x]->setScaledContents(true);
      }
    ///Set's Marshawn's new positions
    marshawns_position->setX(next_x);
    marshawns_position->setY(next_y);
}

/**
 Crush Skittles Function
 * @param Marshawn's position (x,y)
 * @return bool
 * @brief function when the space bar is pressed
 */
bool gameboard::crushSkittles(int x, int y){
    ///Initialize the each of marshawn's vertical (up and down) and horizontal (left and right) axis
    int a=1;
    int left=values[(y*board_size)+(x-a)];
    QLabel* left_label=labels[(y*board_size)+(x-a)];

    int b=1;
    int right = values[(y*board_size)+(x+b)];
    QLabel* right_label = labels[(y*board_size)+(x+b)];

    int c=1;
    int up = values[((y-c)*board_size)+x];
    QLabel* up_label = labels[((y-c)*board_size)+x];

    int d=1;
    int down = values[((y+d)*board_size)+x];
    QLabel* down_label = labels[((y+d)*board_size)+x];

    ///If Marshawn is on the edges
    //If marshawn's on the LEFT most side of the board
    if(x==0)
    {
        left=0;
        values[(y*board_size)+(x-a)]=0;
        //std::cout<<"if(y<15&&x==0) worked for LEFT"<<std::endl;
    }
    //If Marshawn's right next to the LEFT edge BECAUSE it's already been initialized
    //If LEFT is at the left_edge and has no skittle
    else if((x-a)==0 && left==0)
    {
            left=0;
            values[(y*board_size)+(x-a)]=0;
            //std::cout<<"marshawn's right next to the LEFT edge  = 0"<<std::endl;
    }
    ///else While Marshawn's not at the LEFT edge
    else
    {
        while(left==0){
            a++;
            left=values[y*board_size+(x-a)];
            left_label=labels[y*board_size+(x-a)];
            ///when it reaches the edge with no skittle to the left most side
            if((x-a)==0 && left==0){
                left=0;
                //std::cout<<"left edge = 0"<<std::endl;
                break;
            }
            ///when it reaches a skittle to the left, left=that skittle
            else if(left!=0){
            //if((x-a)==0){
                //std::cout<<"left!=0 worked for L"<<std::endl;
                break;
            }
            //a++;
        }
    }
    ///If marshawn's on the RIGHT most side of the board OR next to the right edge BECAUSE it's already been initialized
    if(x==14)
    {
        right=0;
        values[(y*board_size)+(x+b)]=0;
        //std::cout<<"if(y<15&&x==14) worked for Right"<<std::endl;
    }
    //If Marshawn's right next to the RIGHT edge BECAUSE it's already been initialized
    //If RIGHT is at the RIGHT_edge and has no skittle
    else if((x+b)==14 && right==0)
    {
            right=0;
            values[(y*board_size)+(x+b)]=0;
            //std::cout<<"marshawn's right next to the RIGHT edge  = 0"<<std::endl;
    }
    ///else While Marshawn's not at the RIGHT edge
    else
    {
        while(right==0){
            b++;
            right=values[y*board_size+(x+b)];
            right_label=labels[y*board_size+(x+b)];
            if((x+b)==14 && right==0){
                right=0;
                //std::cout<<"right edge = 0"<<std::endl;
                break;
            }
            //when it reaches a skittle to the right, left=that skittle
            else if(right!=0){
            //if((x+b)==0){
                //std::cout<<"right!=0 worked for R"<<std::endl;
                break;
            }
        }
    }
    //If marshawn's on the UP most side of the board
    if(y==0)
    {
        up=0;
        values[((y-c)*board_size)+x]=0;
        //std::cout<<"if(y==14) worked for Up"<<std::endl;
    }
    //If Marshawn's right next to the UP edge BECAUSE it's already been initialized
    //If UP is at the UP_edge and has no skittle
    else if((y-c)==0 && up==0)
    {
            up=0;
            values[((y-c)*board_size)+x]=0;
            //std::cout<<"marshawn's right next to the UP edge  = 0"<<std::endl;
    }
    ///else While Marshawn's not at the UP edge
    else
    {
        while(up==0){
            c++;
            up=values[(y-c)*board_size+x];
            up_label=labels[(y-c)*board_size+x];
            //when UP reaches the top edge
            if((y-c)==0 && up==0){
                up=0;
                //std::cout<<"up edge = 0"<<std::endl;
                break;
            }
            //when UP reaches a skittle, up=that skittle
            else if(up!=0){
            //if((y-c)==0){
                //std::cout<<"up!==0 for U"<<std::endl;
                break;
            }
        }
    }
    //If marshawn's on the DOWN most side of the board
    if(y==14)
    {
        down=0;
        values[((y+d)*board_size)+x]=0;
        //std::cout<<"marshawn's on the DOWN most side of the board"<<std::endl;
    }
    //If Marshawn's right next to the DOW edge BECAUSE it's already been initialized
    //If DOWN is at the DOWN_edge and has no skittle
    else if((y+d)==14 && down==0)
    {
            down=0;
            values[((y+d)*board_size)+x]=0;
            //std::cout<<"marshawn's right next to the DOWN edge  = 0"<<std::endl;
    }
    ///else While Marshawn's not at the DOWN edge
    else
    {
        while(down==0){
            d++;
            down=values[(y+d)*board_size+x];
            down_label=labels[(y+d)*board_size+x];
            if((y+d)==14 && down==0){
                down=0;
                //std::cout<<"at down edge = 0"<<std::endl;
                break;
            }
            else if(down!=0){
            //if((y-c)==0){
                //std::cout<<"not at down edge "<<down<<std::endl;
                break;
            }
        }
    }

    //std::cout<<"L R U D"<< std::endl;
    //std::cout<<left<< " " << right<< " " <<up<< " " <<down<< std::endl;
        if(isValidCrush(x,y, left, right, up, down)) {
            updateAfterCrush(true, values[y*board_size+(x-a)], values[y*board_size+(x+b)], values[(y-c)*board_size+x], values[(y+d)*board_size+x], left_label, right_label, up_label, down_label);
            return true;
        }
        else {
            updateAfterCrush(false, values[y*board_size+(x-a)], values[y*board_size+(x+b)], values[(y-c)*board_size+x], values[(y+d)*board_size+x], left_label, right_label, up_label, down_label);
            return false;
        }
}

        /**
          updateAfterCrush Function
        * @brief updates the gameboard after skittles have been crushed. So if it's invalid crush then you lose a life or the game
        * @param flag
        * @return bool
        */
        void gameboard::updateAfterCrush(bool flag, int& left, int& right, int& up, int& down, QLabel* left_label, QLabel* right_label, QLabel* up_label, QLabel* down_label){
           if(flag){//True
               ///4 SAME SKITTLES LOGIC +12_Points
              if(left==right && left==up && left==down){

                  left_label->clear();left=0;
                  right_label->clear();right=0;
                  up_label->clear();up=0;
                  down_label->clear();down=0;

                  //std::cout<<"left, right, up, and down have been crushed"<<std::endl;
                  //+ 12 POINTS
                  points+=12;
                  type_of_crush = "4 Skittle Crush, +12 Points";
                  return;
               }

              ///2 2 SAME SKITTLES LOGIC +12_Points
              ///Have to be none-zeroes
              if(left!=0 && right!=0 && up!=0 && down!=0){
                  if(left==right && up==down){

                      left_label->clear();left=0;
                      right_label->clear();right=0;
                      up_label->clear();up=0;
                      down_label->clear();down=0;

                      //std::cout<<"left, right, up, and down have been crushed"<<std::endl;
                      //+ 12 POINTS
                      points+=12;
                      type_of_crush = "4 Skittle Crush, +12 Points";
                      return;
                  }
                  if(left==up && right==down){

                      left_label->clear();left=0;
                      right_label->clear();right=0;
                      up_label->clear();up=0;
                      down_label->clear();down=0;

                      //std::cout<<"left, right, up, and down have been crushed"<<std::endl;
                      //+ 12 POINTS
                      points+=12;
                      type_of_crush = "4 Skittle Crush, +12 Points";
                      return;
                  }
                  if(left==down && right==up){

                      left_label->clear();left=0;
                      right_label->clear();right=0;
                      up_label->clear();up=0;
                      down_label->clear();down=0;

                      //std::cout<<"left, right, up, and down have been crushed"<<std::endl;
                      //+ 12 POINTS
                      points+=12;
                      type_of_crush = "4 Skittle Crush, +12 Points";
                      return;
                  }

              }

              ///3 SAME SKITTLES LOGIC +6_Points
              if(left==up && left==down){

                  up_label->clear();up=0;
                  down_label->clear();down=0;
                  left_label->clear();left=0;

                  //std::cout<<"up, down, left have been crushed"<<std::endl;
                  //+6 POINTS
                  points+=6;
                  type_of_crush = "3 Skittle Crush, +6 Points";
                  return;
              }
              if(left==right && left==up){

                  left_label->clear();left=0;
                  right_label->clear();right=0;
                  up_label->clear();up=0;

                  //std::cout<<"left, right, up have been crushed"<<std::endl;
                  //+6 POINTS
                  points+=6;
                  type_of_crush = "3 Skittle Crush, +6 Points";
                  return;
              }
              if(right==up && right==down){

                  up_label->clear();up=0;
                  down_label->clear();down=0;
                  right_label->clear();right=0;

                  //std::cout<<"up, down, right have been crushed"<<std::endl;
                  //+6 POINTS
                  points+=6;
                  type_of_crush = "3 Skittle Crush, +6 Points";
                  return;
              }
              if(left==right && left==down){

                  left_label->clear();left=0;
                  right_label->clear();right=0;
                  down_label->clear();down=0;

                  //std::cout<<"left, right, down have been crushed"<<std::endl;
                  //+6 POINTS
                  points+=6;
                  type_of_crush = "3 Skittle Crush, +6 Points";
                  return;
              }

              ///TWO SAME SKITTLES LOGIC +2_Points
              if(left==right && left!=0){

                left_label->clear();left=0;
                right_label->clear();right=0;

                //std::cout<<"left and right have been crushed"<<std::endl;
                ///+2
                points+=2;
                type_of_crush = "2 Skittle Crush, +2 Points";
                return;
              }
              if(up==down && up!=0){

                up_label->clear();up=0;
                down_label->clear();down=0;

                //std::cout<<"up and down have been crushed"<<std::endl;
                points+=2;
                type_of_crush = "2 Skittle Crush, +2 Points";
                return;
              }
              if(left==up && left!=0){

                left_label->clear();left=0;
                up_label->clear();up=0;

                //std::cout<<"left and up have been crushed"<<std::endl;
                //+2
                points+=2;
                type_of_crush = "2 Skittle Crush, +2 Points";
                return;
              }
              if(left==down && left!=0){

                left_label->clear();left=0;
                down_label->clear();down=0;

                //std::cout<<"left and down have been crushed"<<std::endl;
                //+2
                points+=2;
                type_of_crush = "2 Skittle Crush, +2 Points";
                return;
              }
              if(right==up && up!=0){

                right_label->clear();right=0;
                up_label->clear();up=0;

                //std::cout<<"right and up have been crushed"<<std::endl;
                //+2
                points+=2;
                type_of_crush = "2 Skittle Crush, +2 Points";
                return;
              }
              if(right==down && right!=0){

                right_label->clear();right=0;
                down_label->clear();down=0;

                //std::cout<<"right and down have been crushed"<<std::endl;
                //+2
                points+=2;
                type_of_crush = "2 Skittle Crush, +2 Points";
                return;
              }

           }

           else {//false
               ///if it's an invalid CRUSH then lose a life or the game if life runs out.
               if(lives_remaining > 0) {
                   lives_remaining--;
                   lives[lives_remaining]->clear();
                   type_of_crush = "INVALID CRUSH! You lost a life";
                   return;
               }
               else {
                   gamedone();
                   return;
               }
           }
           game_is_over = false;
        }
        /**
         * @brief Game logic to crush skittles based on Marshawn's position (@param)
         * @param Marshawn's position (x,y)
         * @return bool
         */
        bool gameboard::isValidCrush(int x, int y, int left, int right, int up, int down) {
              if(values[y*board_size+x]==0){
                  ///if the skittles match but they CANNOT be 0 aka no skittles.
                  if((left==right && left!=0)||(up==down && up!=0)   ||
                          (left==up&&left!=0)||(left==down && left!=0)   ||
                          (right==up&&right!=0)||(right==down&&right!=0)){
                      return true;
                  }
                  else
                    return false;
              }
              return false;
        }
/**
 paintevent

 @param
 @return void
 @brief Paints the gameboard, gameboard variable objects, and Marshawn
 */
void gameboard::paintEvent(QPaintEvent *e) {

    if(game_is_over){

        if(clock->getSeconds()==0) gamedone();

        size_t x = marshawns_position->rx();
        size_t y = marshawns_position->ry();

        labels[y*board_size+x]->setPixmap(*marshawns_image);
        labels[y*board_size+x]->setScaledContents(true);

        /** Painting Score */
        score_lcd->setNum(points);
        /** Painting Skittles Crush*/
        crush_output->setText(type_of_crush);
        if(lives_remaining==0) gamedone();
    }

game_is_over = true;
}

/**
 ShowEvent

 @param
 @return
 @brief
 */
void gameboard::showEvent(QShowEvent *e) {
    this->activateWindow();
    this->setFocus();
    QWidget::showEvent(e);
}

/**
 SLOT - Set GameOver Window
 @param gameover* go
 @brief When game is over, a GameOver Window pops up asking the user if he wants to "quit" or "play again"
 */
void gameboard::setGameOverWindow(gameover* go){
    gameOver_object = go;
}

/**
 Start Game Function
 @param
 @brief set's the MainWindow to the gameboard object
 *  Color of the board is set to red here
 */
void gameboard::startGame(){
    this->setStyleSheet("background-color: red;");
    show();
}
/**
 Start Done/Game Over Function
 @param
 @brief set's the MainWindow to the gameboard object
 *  Color of the board is set to red here
 */
void gameboard::gamedone(){
    clock->stop();
    game_is_over=true;
    gameOver_object->show();
}
