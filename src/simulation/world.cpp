#include "world.h"
#include <iostream>
#include <QDebug>

using namespace std;

World::World(b2Vec2 gravity, b2Vec2 size, size_t bufferSize,
             GeneticParameters params):
    simulation_(gravity, size, bufferSize, params)
{
    int interval = 1000/60; //60 fps
    drawTimer_.setInterval(interval);
    setUpdateInterval(interval*1);
    setCreateObjectInterval(interval * 1);

    QObject::connect(&drawTimer_, SIGNAL(timeout()),
                     this, SLOT(advance()));
    QObject::connect(&updateTimer_, SIGNAL(timeout()),
                     &simulation_, SLOT(onUpdateTimeout()));
    QObject::connect(&createObjectTimer_, SIGNAL(timeout()),
                     &simulation_, SLOT(onCreateObjectTimeout()));

    QObject::connect(&simulation_, SIGNAL(removeItem(Car*)),
                     this, SLOT(removeItem(Car*)));
    QObject::connect(&simulation_, SIGNAL(addItem(Car*)),
                     this, SLOT(addItem(Car*)));
    QObject::connect(this, SIGNAL(removeObject()),
                     &simulation_, SLOT(removeObject()));
    QObject::connect(this, SIGNAL(addObject()),
                     &simulation_, SLOT(addObject()));
    simulation_.initialize(*this);
    simulation_.moveToThread(&thread_);
    thread_.start();
}

World::~World()
{
   //thread_.terminate();
   //thread_.wait();
}

//TODO change Object to Item class name
void World::start()
{
//    qDebug() << "Start ThreadID: " << QThread::currentThreadId();
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

void World::removeItem(Car* o)
{
//   qDebug() << "Removing item[" << o->id() << "] from scene";
    QGraphicsScene::removeItem(o);
    emit removeObject();
}

void World::addItem(Car* o)
{
    qDebug() << "SCENE: Adding item[" << o->id() << "]";
    QGraphicsScene::addItem(o);
    emit addObject();
}

void World::stop()
{
    drawTimer_.stop();
    updateTimer_.stop();
    createObjectTimer_.stop();
}

void World::setUpdateInterval(int interval)
{
    updateTimer_.setInterval(interval);
}

void World::setCreateObjectInterval(int interval)
{
    createObjectTimer_.setInterval(interval);
}
