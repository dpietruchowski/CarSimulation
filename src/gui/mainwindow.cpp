#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QDebug>
#include <QTime>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), world(b2Vec2(0.0f, -80.0f), b2Vec2(1000.0f, 50.0f),
                                  60, {30, SelectionType::RANK_ROULETTESELECTION},
                                  600)
{
    ui->setupUi(this);
    nwDialog = new NewWorldDialog(this);
    QObject::connect(nwDialog, SIGNAL(accepted()), this, SLOT(newWorld()));
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
    QObject::connect(&world, SIGNAL(update()),
                     this, SLOT(update()));

    ui->carView->setScene(&carScene);
    ui->carView->setRenderHint(QPainter::Antialiasing);
    transform = ui->carView->transform();
    transform.scale(10.0f, -10.0f);
    transform.translate(10.0f, -40.0f);
    ui->carView->setTransform(transform);
    ui->carView->centerOn(0,0);

    QStringList labels;
    labels << "Id" << "Score";
    ui->carTableWidget->setHorizontalHeaderLabels(labels);
    QHeaderView *verticalHeader = ui->carTableWidget->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(15);
    ui->carTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->carTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->carTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->worldProgressBar->setMaximum(world.maxTime() * 1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addObject(int row, CarSPtr car)
{
    //ui->carListWidget->insertItem(row, QString::number(car->id()));
    ui->carTableWidget->insertRow(row);
    ui->carTableWidget->setItem(row, 0, new QTableWidgetItem(
                                                QString::number(car->id())));
    ui->carTableWidget->setItem(row, 1, new QTableWidgetItem(
                                                QString::number(car->score())));
}

void MainWindow::removeObject(int row, CarSPtr car)
{
    //auto list = ui->carListWidget;
    //list->removeItemWidget(list->takeItem(row));
    auto table = ui->carTableWidget;
    table->removeRow(row);
}

void MainWindow::update()
{
    QTime time(0,0,0);
    QTime worldTime = time.addMSecs(world.time()*1000);
    ui->timeMSView->display(worldTime.msec());
    ui->timeSView->display(worldTime.second());
    ui->timeMView->display(worldTime.minute());
    ui->timeHView->display(worldTime.hour());

    ui->worldProgressBar->setValue(world.time() * 1000);

    ui->nCarsAliveValue->setText(QString::number(world.scene().nCarsAlive()));
    ui->nCarsCreatedValue->setText(QString::number(world.scene().nCarsCreated()));
    ui->nCarsKilledValue->setText(QString::number(world.scene().nCarsKilled()));
    ui->bestScoreValue->setText(QString::number(world.bestScore()));
    ui->avScoreValue->setText(QString::number(world.avarageScore()));
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

/* void MainWindow::on_carListWidget_currentTextChanged(const QString &currentText)
{
    QList<QGraphicsItem *> sceneItems = carScene.items();
    for(const auto &item: sceneItems) {
        carScene.removeItem(item);
    }
    ui->carView->centerOn(0,0);
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
} */

void MainWindow::on_carTableWidget_cellPressed(int row, int /* column */)
{
    const QString &currentText = ui->carTableWidget->item(row, 0)->text();

    QList<QGraphicsItem *> sceneItems = carScene.items();
    for(const auto &item: sceneItems) {
        carScene.removeItem(item);
    }
    ui->carView->centerOn(0,0);
    auto ind = std::find_if(world.individuals().begin(),
                            world.individuals().end(),
                            [&currentText](const std::pair<double, CarSPtr> &p)->bool
                            {
                                auto id = currentText.toInt();
                                return p.second->id() == id;
                            });

    if(ind == world.individuals().end())
        throw "Didnt find this car";
    carScene.addItem(ind->second.get());
}

void MainWindow::on_carTableWidget_cellEntered(int row, int column)
{
    on_carTableWidget_cellPressed(row, column);
}

void MainWindow::on_pushButton_5_clicked()
{
    nwDialog->setDefault();
    nwDialog->show();
}

void MainWindow::newWorld()
{
    std::cout << "New World" << std::endl;
    nwDialog->showValues();
}
