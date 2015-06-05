#include "mainwindow.h"
#include <QApplication>
#include "gameboard.h"
#include "lcdnumber.h"
#include "gameover.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* mw = new MainWindow;
    instructions* i = new instructions;

    mw->setInstructionsWindow(i);
    mw->show();
    return a.exec();
}
