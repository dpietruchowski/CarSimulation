#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QDebug>
#include <QTime>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), currentWorldIndex(-1)
{
    ui->setupUi(this);
    nwDialog = new NewWorldDialog(this);
    QObject::connect(nwDialog, SIGNAL(accepted()), this, SLOT(newWorld()));

    QStringList labels;
    labels << "Id" << "Score";
    ui->carTableWidget->setHorizontalHeaderLabels(labels);
    QHeaderView *verticalHeader = ui->carTableWidget->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(15);
    ui->carTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->carTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->carTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->worldView->setRenderHint(QPainter::Antialiasing);
    QTransform transform = ui->worldView->transform();
    transform.scale(5.0f, -5.0f);
    transform.translate(10.0f, -40.0f);
    ui->worldView->setTransform(transform);
    ui->worldView->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);

    ui->carView->setScene(&carScene);
    ui->carView->setRenderHint(QPainter::Antialiasing);
    transform = ui->carView->transform();
    transform.scale(10.0f, -10.0f);
    transform.translate(10.0f, -40.0f);
    ui->carView->setTransform(transform);
    ui->carView->centerOn(0,0);

    ui->startButton->setEnabled(false);
    ui->forwardButton->setEnabled(false);
    ui->carTableWidget->setEnabled(false);
    ui->nextWorldButton->setEnabled(false);
    ui->previoustWorldButton->setEnabled(false);
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
    QTime worldTime = time.addMSecs(worlds[currentWorldIndex]->time() * 1000);
    ui->timeMSView->display(worldTime.msec());
    ui->timeSView->display(worldTime.second());
    ui->timeMView->display(worldTime.minute());
    ui->timeHView->display(worldTime.hour());

    ui->worldProgressBar->setValue(worlds[currentWorldIndex]->time() * 1000);

    ui->nCarsAliveValue->setText(QString::number(worlds[currentWorldIndex]->scene().nCarsAlive()));
    ui->nCarsCreatedValue->setText(QString::number(worlds[currentWorldIndex]->scene().nCarsCreated()));
    ui->nCarsKilledValue->setText(QString::number(worlds[currentWorldIndex]->scene().nCarsKilled()));
    ui->bestScoreValue->setText(QString::number(worlds[currentWorldIndex]->bestScore()));
    ui->avScoreValue->setText(QString::number(worlds[currentWorldIndex]->avarageScore()));
}

void MainWindow::on_forwardButton_toggled(bool checked)
{
    worlds[currentWorldIndex]->forward(checked);
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
        worlds[currentWorldIndex]->start();
        ui->startButton->setText(QString("Pause"));
    } else
    {
        worlds[currentWorldIndex]->stop();
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
    auto ind = std::find_if(worlds[currentWorldIndex]->individuals().begin(),
                            worlds[currentWorldIndex]->individuals().end(),
                            [&currentText](const std::pair<double, CarSPtr> &p)->bool
                            {
                                auto id = currentText.toInt();
                                return p.second->id() == id;
                            });

    if(ind == worlds[currentWorldIndex]->individuals().end())
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
    //    nwDialog->showValues();


    worlds.push_back(unique_ptr<World>(new World(
                nwDialog->gravity(),
                nwDialog->worldSize(),
                nwDialog->bufferSize(),
                nwDialog->geneticParameters(),
                nwDialog->maxWorldTime()
                )));

    if(worlds.size() > 0) {
        ui->startButton->setEnabled(true);
        ui->forwardButton->setEnabled(true);
        ui->carTableWidget->setEnabled(true);
    }
    if(worlds.size() > 1)
        ui->previoustWorldButton->setEnabled(true);
    ui->nextWorldButton->setEnabled(false);
    currentWorldIndex = worlds.size() - 1;
    setWorld(currentWorldIndex);
}

void MainWindow::removeWorld(int worldIndex)
{
    if(currentWorldIndex == worldIndex) {
        // if it is only one world set none world
        if(worlds.size() == 1) {
            clearUi();
        } else if(currentWorldIndex == worlds.size() - 1) {
            // if it is last world
            on_previoustWorldButton_clicked();
        } else {
            on_nextWorldButton_clicked();
        }
    } else if(worldIndex < currentWorldIndex) {
        --currentWorldIndex;
    }

    worlds.erase(worlds.begin() + worldIndex);
    if(worlds.size() <= 0) {
        ui->startButton->setEnabled(false);
        ui->forwardButton->setEnabled(false);
        ui->carTableWidget->setEnabled(false);
        ui->nextWorldButton->setEnabled(false);
        ui->previoustWorldButton->setEnabled(false);
    }
}

void MainWindow::setWorld(int worldIndex)
{
    clearBeforeSet();
    ///////////////////////////////////////////
    currentWorldIndex = worldIndex;
    ui->worldLabel->setText(QString::number(worldIndex));

    ui->worldView->setScene(&worlds[currentWorldIndex]->scene());
    ui->worldView->setSceneRect(-20,-55,1050,110);
    ui->worldView->centerOn(0,0);

    ui->worldProgressBar->setMaximum(worlds[currentWorldIndex]->maxTime() * 1000);

    QObject::connect(worlds[currentWorldIndex].get(), SIGNAL(addObject(int, CarSPtr)),
                     this, SLOT(addObject(int, CarSPtr)));
    QObject::connect(worlds[currentWorldIndex].get(), SIGNAL(removeObject(int, CarSPtr)),
                     this, SLOT(removeObject(int, CarSPtr)));
    QObject::connect(worlds[currentWorldIndex].get(), SIGNAL(update()),
                     this, SLOT(update()));
}

void MainWindow::on_nextWorldButton_clicked()
{
    setWorld(++currentWorldIndex);
    ui->previoustWorldButton->setEnabled(true);
    if(currentWorldIndex == worlds.size() - 1)
        ui->nextWorldButton->setEnabled(false);

}

void MainWindow::on_previoustWorldButton_clicked()
{
    setWorld(--currentWorldIndex);
    ui->nextWorldButton->setEnabled(true);
    if(currentWorldIndex == 0)
        ui->previoustWorldButton->setEnabled(false);
}

void MainWindow::clearBeforeSet()
{
    if(currentWorldIndex >= 0) {
        QObject::disconnect(worlds[currentWorldIndex].get(), SIGNAL(addObject(int, CarSPtr)),
                        this, SLOT(addObject(int, CarSPtr)));
        QObject::disconnect(worlds[currentWorldIndex].get(), SIGNAL(removeObject(int, CarSPtr)),
                        this, SLOT(removeObject(int, CarSPtr)));
        QObject::disconnect(worlds[currentWorldIndex].get(), SIGNAL(update()),
                        this, SLOT(update()));
    }

    carScene.clear();
    ui->carTableWidget->clear();
    ui->carTableWidget->setRowCount(0);

    ui->avScoreValue->setText(QString::number(0));
    ui->bestScoreValue->setText(QString::number(0));
    ui->nCarsAliveValue->setText(QString::number(0));
    ui->nCarsCreatedValue->setText(QString::number(0));
    ui->nCarsKilledValue->setText(QString::number(0));

    ui->timeHView->display(0);
    ui->timeMSView->display(0);
    ui->timeMView->display(0);
    ui->timeSView->display(0);
    ui->worldProgressBar->setValue(0);
}

void MainWindow::clearUi()
{
    clearBeforeSet();
    ui->startButton->setEnabled(false);
    ui->forwardButton->setEnabled(false);
    ui->carTableWidget->setEnabled(false);
    ui->nextWorldButton->setEnabled(false);
    ui->previoustWorldButton->setEnabled(false);

    ui->worldView->setScene(new QGraphicsScene(ui->worldView));

    ui->worldLabel->setText(QString("none"));
}
