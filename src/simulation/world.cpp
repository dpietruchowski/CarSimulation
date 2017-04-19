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
             const GeneticParameters& params, double maxTime):
    simulation_({10, 100}, gravity, size, bufferSize, params), time_(0),
    maxTime_(maxTime), isRunning_(false)
{
    int interval = 1000/60; //60 fps
    drawTimer_.setInterval(interval*1);
    setUpdateInterval(interval*1);
    setCreateObjectInterval(interval * 10);

    QObject::connect(&simulation_.genetic(), SIGNAL(addObject(CarSPtr)),
                     this, SLOT(addObject(CarSPtr)));
    QObject::connect(&simulation_.genetic(), SIGNAL(removeObject(CarSPtr)),
                     this, SLOT(removeObject(CarSPtr)));

    QObject::connect(&drawTimer_, SIGNAL(timeout()),
                     &scene_, SLOT(advance()));
    QObject::connect(&updateTimer_, SIGNAL(timeout()),
                     &simulation_, SLOT(onUpdateTimeout()),
                     Qt::BlockingQueuedConnection);
    QObject::connect(&createObjectTimer_, SIGNAL(timeout()),
                     &simulation_, SLOT(onCreateObjectTimeout()),
                     Qt::BlockingQueuedConnection);

    qRegisterMetaType<CarSPtr>();
    QObject::connect(&simulation_, SIGNAL(removeItem(CarSPtr)),
                     &scene_, SLOT(removeItem(CarSPtr)));
    QObject::connect(&simulation_, SIGNAL(addItem(QGraphicsItem*)),
                     &scene_, SLOT(addItem(QGraphicsItem*)));
    qDebug() << "Constructor Thread ID: " << QThread::currentThreadId();

    QObject::connect(this, SIGNAL(initialize()),
                     &simulation_, SLOT(initialize()));
    QObject::connect(&simulation_, SIGNAL(setTime(double)),
                     &scene_, SLOT(setTime(double)));
    QObject::connect(&simulation_, SIGNAL(setTime(double)),
                     this, SLOT(setTime(double)));
    simulation_.moveToThread(&thread_);
    emit initialize();
    thread_.start();

}

World::~World()
{
   thread_.terminate();
   thread_.wait();
}

void World::start()
{
//    qDebug() << "Start ThreadID: " << QThread::currentThreadId();
    isRunning_ = true;
    startDrawing();
    updateTimer_.start();
    createObjectTimer_.start();
}

void World::pause()
{
//    qDebug() << "Pause ThreadID: " << QThread::currentThreadId();
    isRunning_ = false;
    stopDrawing();
    updateTimer_.stop();
    createObjectTimer_.stop();
}

void World::stop()
{
    isRunning_ = false;
    stopDrawing();
    updateTimer_.stop();
    createObjectTimer_.stop();
}

void World::stopDrawing()
{
    drawTimer_.stop();
}

void World::startDrawing()
{
    drawTimer_.start();
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

double World::avarageScore() const
{
    double sum = 0;
    for(const auto &ind: individuals_)
    {
        sum += ind.first;
    }

    return sum / individuals_.size();
}

double World::bestScore() const
{
    return individuals_.begin()->first;
}

bool World::isRunning() const
{
    return isRunning_;
}

WorldScene &World::scene()
{ return scene_; }

double World::time() const
{ return time_; }

double World::maxTime() const
{ return maxTime_; }

World::Individuals &World::individuals()
{ return individuals_; }

const Simulation &World::simulation() const
{ return simulation_; }

void World::addObject(CarSPtr ind)
{
    auto inserted = individuals_.insert(make_pair(ind->score(), ind));
    if(!inserted.second)
        throw "Cannot insert individual";
    int dist = distance(individuals_.begin(), inserted.first);
    emit addObject(dist, inserted.first->second);
}

void World::removeObject(CarSPtr ind)
{
    auto erased = individuals_.find(ind->score());
    int dist = distance(individuals_.begin(), erased);
    auto erasedNumber = individuals_.erase(erased);
    if(erasedNumber != individuals_.end())
        throw "Erased more or less elements";
    emit removeObject(dist, erased->second);
}

void World::setTime(double time)
{
    time_ = time;
    if(time_ > maxTime_)
    {
        stop();
    }
    emit update();
}
