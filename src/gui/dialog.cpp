#include "dialog.h"
#include "ui_dialog.h"
#include <sstream>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::operator<<(std::stringstream &os)
{
    ui->textBrowser->append(QString::fromStdString(os.str()));
}

void Dialog::operator<=(std::stringstream &os)
{
    ui->textBrowser_2->append(QString::fromStdString(os.str()));
}

void Dialog::clear(int number)
{
    if(number == 0)
        ui->textBrowser->clear();
    else
        ui->textBrowser_2->clear();
}
