#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), world(b2Vec2(0.0f, -80.0f), b2Vec2(1000.0f, 50.0f),
                                  60, {30, SelectionType::RANK_ROULETTESELECTION})
{
    ui->setupUi(this);
    ui->worldView->setScene(&world);
    ui->worldView->setSceneRect(-20,-55,1050,110);
    ui->worldView->centerOn(0,0);
    ui->worldView->setRenderHint(QPainter::Antialiasing);
    QTransform transform = ui->worldView->transform();
    transform.scale(5.0f, -5.0f);
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
    qDebug() << "BUtton ThreadID: " << QThread::currentThreadId();
    world.start();
}

void MainWindow::on_forwardButton_toggled(bool checked)
{
    world.forward(checked);
    if(checked)
    {
//        ui->worldView->setScene(nullptr);
        ui->forwardButton->setText(QString("Normal"));
    } else
    {
//        ui->worldView->setScene(&world);
        ui->forwardButton->setText(QString("Forward"));
    }
}
