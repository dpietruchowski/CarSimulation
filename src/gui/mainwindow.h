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
    void addObject(int, CarSPtr);
    void removeObject(int, CarSPtr);
    void update();
    void on_forwardButton_toggled(bool checked);
    void on_startButton_toggled(bool checked);
//    void on_carListWidget_currentTextChanged(const QString &currentText);
    void on_carTableWidget_cellPressed(int row, int column);
    void on_carTableWidget_cellEntered(int row, int column);

private:
    Ui::MainWindow *ui;
    World world;
    QGraphicsScene carScene;
};

#endif // MAINWINDOW_H
