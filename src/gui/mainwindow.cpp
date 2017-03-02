#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QDebug>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), world(b2Vec2(0.0f, -80.0f), b2Vec2(1000.0f, 50.0f),
                                  60, {30, SelectionType::RANK_ROULETTESELECTION})
{
    ui->setupUi(this);
    ui->worldView->setScene(&world.scene());
    ui->worldView->setSceneRect(-20,-55,1050,110);
    ui->worldView->centerOn(0,0);
    ui->worldView->setRenderHint(QPainter::Antialiasing);
    QTransform transform = ui->worldView->transform();
    transform.scale(5.0f, -5.0f);
    transform.translate(10.0f, -40.0f);
    ui->worldView->setTransform(transform);
    ui->worldView->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);

    QObject::connect(&world, SIGNAL(addObject(int, CarSPtr)),
                     this, SLOT(addObject(int, CarSPtr)));
    QObject::connect(&world, SIGNAL(removeObject(int, CarSPtr)),
                     this, SLOT(removeObject(int, CarSPtr)));

    ui->carView->setScene(&carScene);
    ui->carView->centerOn(0,0);
    ui->carView->setRenderHint(QPainter::Antialiasing);
    transform = ui->carView->transform();
    transform.scale(5.0f, -5.0f);
    transform.translate(10.0f, -40.0f);
    ui->carView->setTransform(transform);
    carScene.addLine(0, -20, 0, 20);
    carScene.addLine(-20, 0, 20, 0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addObject(int row, CarSPtr car)
{
    ui->carListWidget->insertItem(row, QString::number(car->id()));
}

void MainWindow::removeObject(int row, CarSPtr car)
{
    auto list = ui->carListWidget;
    list->removeItemWidget(list->takeItem(row));
}

void MainWindow::updateTime()
{

}

void MainWindow::on_forwardButton_toggled(bool checked)
{
    world.forward(checked);
    if(checked)
    {
        ui->forwardButton->setText(QString("Normal"));
    } else
    {
        ui->forwardButton->setText(QString("Faster"));
    }
}
void MainWindow::on_startButton_toggled(bool checked)
{
    if(checked)
    {
        world.start();
        ui->startButton->setText(QString("Pause"));
    } else
    {
        world.stop();
        ui->startButton->setText(QString("Resume"));
    }
}

void MainWindow::on_carListWidget_currentTextChanged(const QString &currentText)
{
    QList<QGraphicsItem *> sceneItems = carScene.items();
    for(const auto &item: sceneItems) {
        carScene.removeItem(item);
    }
 //   carScene.addLine(0, -20, 0, 20);
  //  carScene.addLine(-20, 0, 20, 0);
    auto ind = std::find_if(world.individuals().begin(),
                            world.individuals().end(),
                            [&currentText](const std::pair<double, CarSPtr> &p)->bool
                            {
                                auto id = currentText.toInt();
                                cout << id << " ";
                                cout << p.second->id() << endl;
                                return p.second->id() == id;
                            });

    if(ind == world.individuals().end())
        throw "Didnt find this car";
    carScene.addItem(ind->second.get());
}
