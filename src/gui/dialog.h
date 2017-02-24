#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <sstream>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void operator<<(std::stringstream &os);
    void operator<=(std::stringstream &os);

    void clear(int number);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
