#include "lcdnumber.h"
#include "ui_lcdnumber.h"

lcdnumber::lcdnumber(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lcdnumber)
{
    ui->setupUi(this);
}

lcdnumber::~lcdnumber()
{
    delete ui;
}
