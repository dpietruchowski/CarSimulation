#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simulation/world.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_forwardButton_toggled(bool checked);
    void on_startButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    World world;
};

#endif // MAINWINDOW_H
