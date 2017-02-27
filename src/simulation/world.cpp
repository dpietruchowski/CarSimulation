#include "world.h"
#include <iostream>
#include <QDebug>

using namespace std;

namespace {
    unsigned int TimeoutCounter = 0;
}

void World::incTimeout() {
    //qDebug() << "Timeout counter: " << TimeoutCounter++;
}

World::World(b2Vec2 gravity, b2Vec2 size, size_t bufferSize,
             GeneticParameters params):
    simulation_({10, 100}, gravity, size, bufferSize, params)
{
    int interval = 1000/60; //60 fps
    drawTimer_.setInterval(interval*1);
    setUpdateInterval(interval*1);
    setCreateObjectInterval(interval * 10);

    QObject::connect(&drawTimer_, SIGNAL(timeout()),
                     this, SLOT(advance()));
    QObject::connect(&updateTimer_, SIGNAL(timeout()),
                     &simulation_, SLOT(onUpdateTimeout()),
                     Qt::BlockingQueuedConnection);
    QObject::connect(&createObjectTimer_, SIGNAL(timeout()),
                     &simulation_, SLOT(onCreateObjectTimeout()),
                     Qt::BlockingQueuedConnection);

    qRegisterMetaType<CarSPtr>();
    QObject::connect(&simulation_, SIGNAL(removeItem(CarSPtr)),
                     this, SLOT(removeItem(CarSPtr)));
    QObject::connect(&simulation_, SIGNAL(addItem(QGraphicsItem*)),
                     this, SLOT(addItem(QGraphicsItem*)));
    qDebug() << "Constructor Thread ID: " << QThread::currentThreadId();

    QObject::connect(this, SIGNAL(initialize()),
                     &simulation_, SLOT(initialize()));
    QObject::connect(&simulation_, SIGNAL(setTime(double)),
                     this, SLOT(setTime(double)));
    simulation_.moveToThread(&thread_);
    emit initialize();
    thread_.start();

    timeDrawer_.setPos(-10,-10);
    QFont myFont;
    myFont.setPointSizeF(1.0);
    myFont.setPixelSize(5);
    myFont.setFamily("Courier");
    QTransform transform;
    transform.scale(1, -1);
    timeDrawer_.setTransform(transform);
    timeDrawer_.setFont(myFont);
    timeDrawer_.setPlainText(QString::number(0));
    addItem(&timeDrawer_);
}

World::~World()
{
   thread_.terminate();
   thread_.wait();
}

void World::start()
{
    qDebug() << "Start ThreadID: " << QThread::currentThreadId();
    drawTimer_.start();
    updateTimer_.start();
    createObjectTimer_.start();
}

void World::pause()
{
//    qDebug() << "Pause ThreadID: " << QThread::currentThreadId();
    drawTimer_.stop();
    updateTimer_.stop();
    createObjectTimer_.stop();
}


void World::addItem(QGraphicsItem* o)
{
//    qDebug() << "SCENE: Adding item[" << o->id() << "]";
    QGraphicsScene::addItem(o);
}

void World::removeItem(CarSPtr o)
{
//    qDebug() << "SCENE: Removing item[" << o->id() << "]";
    QGraphicsScene::removeItem(o.get());
}

void World::setTime(double time)
{
    timeDrawer_.setPlainText(QString::number(time));
}

void World::stop()
{
    drawTimer_.stop();
    updateTimer_.stop();
    createObjectTimer_.stop();
}

void World::forward(bool clicked)
{
    int interval = 1000/60; //60 fps
    double rate = 1;

    if(clicked)
    {
        //simulation_.blockSignals(true);
        rate = 3.0;
    } else
    {
        //simulation_.blockSignals(false);
        rate = 1.0;
    }
    simulation_.setInterval(rate / 60);
    setUpdateInterval(interval / rate);
    setCreateObjectInterval((interval * 10) / rate);
}

void World::setUpdateInterval(int interval)
{
    updateTimer_.setInterval(interval);
}

void World::setCreateObjectInterval(int interval)
{
    createObjectTimer_.setInterval(interval);
}
