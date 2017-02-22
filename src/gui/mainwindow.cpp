#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), world(b2Vec2(0.0f, -80.0f), b2Vec2(1000.0f, 200.0f))
{
    ui->setupUi(this);
    ui->worldView->setScene(&world);
    ui->worldView->setSceneRect(-20,-110,1050,220);
    ui->worldView->setRenderHint(QPainter::Antialiasing);
    QTransform transform = ui->worldView->transform();
    transform.scale(2.0f, -2.0f);
    transform.translate(10.0f, -40.0f);
    ui->worldView->setTransform(transform);
    ui->worldView->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_stopButton_clicked()
{
    world.stop();
}

void MainWindow::on_startButton_clicked()
{
    world.start();
}
