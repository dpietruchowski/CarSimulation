#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "simulation/world.h"
#include "newworlddialog.h"

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
    void on_startButton_toggled(bool checked);
//    void on_carListWidget_currentTextChanged(const QString &currentText);
    void on_carTableWidget_cellPressed(int row, int column);
    void on_carTableWidget_cellEntered(int row, int column);

    void on_pushButton_5_clicked();

    void newWorld();
    void removeWorld();
    void setWorld(int worldIndex);

    void on_nextWorldButton_clicked();

    void on_previoustWorldButton_clicked();

    void clearBeforeSet();
    void clearUi();

private:
    NewWorldDialog *nwDialog;
    Ui::MainWindow *ui;
    int currentWorldIndex;
    std::vector<std::unique_ptr<World>> worlds;
    QGraphicsScene carScene;
};

#endif // MAINWINDOW_H
