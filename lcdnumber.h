/** @file LCDNumber.h
    @author Kevin Kim
    @date
    @brief This is a header file for the LCDNumber class. The class is defined within this header file.
    This file contains the list of functions and variable used in LCDNumber.
    The LCDNumber class contains the timer for the game.
    It keeps track of the game time.
*/

#ifndef LCDNUMBER_H
#define LCDNUMBER_H

#include <QLCDNumber>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include "gameboard.h"
class LCDNumber:  public QLabel
{
  Q_OBJECT

  public:
  QTimer* timer;
  QTime*  timeValue;
  int sec;
  int set_min;
  int set_sec;

  public:
  /** LCDNumber Constructor
     * @brief builds the clock object used as a timer in the game
     */
    LCDNumber(QWidget * parentWidget,int minutes,int seconds)
    {
        set_min = minutes;
        set_sec = seconds;
        timer = new QTimer();
        timeValue = new QTime(0,minutes,seconds);
        sec = minutes*60 + seconds;
        this->setParent(parentWidget);
        this->setText(timeValue->toString());
        QObject::connect(timer,SIGNAL(timeout()),this,SLOT(setDisplay()));
    };
    ~ LCDNumber(){};

    int getSeconds() { return sec;}
    void start() { timer->start();}
    void stop() { timer->stop();}
    void restart(){
        timeValue->setHMS(0, set_min, set_sec, 0);
        sec = set_min*60+set_sec;
    }
public slots:
    void setDisplay()
    {
      this->timeValue->setHMS(0,this->timeValue->addSecs(-1).minute(),this->timeValue->addSecs(-1).second());
        sec--;
      this->setText(this->timeValue->toString());
    };
};
#endif
