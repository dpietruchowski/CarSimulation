#include "simulation.h"
#include <QThread>
#include <ctime>
#include <QDebug>
#include "object/car.h"
#include "object/ground.h"
#include <iostream>
#include "utilfunctions.h"

using namespace std;

const float32 Simulation::CLICKED_DISTANCE = 10;

namespace {
unsigned int UpdateCounter = 0;
unsigned int CreateCounter = 0;
}

Simulation::Simulation(b2Vec2 initPosition, b2Vec2 gravity, b2Vec2 size,
                       size_t bufferSize, const GeneticParameters& params):
    initPosition_(initPosition), world_(gravity), ground_(size),
    size_(size), genetic_(params), buffer_(bufferSize), interval_(1.0/60), time_(0)
{
}

void Simulation::initialize()
{
    qDebug() << "Initialize Thread ID: " << QThread::currentThreadId();
    ground_.create(world_);
    emit addItem(&ground_);
    for(size_t i = 0; i < buffer_.maxSize(); ++i)
        buffer_.push(CarPtr(new Car(b2Vec2(initPosition_))));
}

void Simulation::setInterval(double interval)
{
    interval_ = interval;
}

void Simulation::update()
{
    int i = 0;
    for (Objects::iterator it = objects_.begin(); it != objects_.end();)
    {
        Car *o = it->get();
        o->update(interval_);

        float32 x = o->getPosition().x;
        o->calcScore();

        // For easy debbuging
        if ( (!o->isMoving(interval_)) )
        { killObject(it); continue; }
        if ( (x > size_.x) )
        { killObject(it); continue; }
        if ( (x < 0) )
        { killObject(it); continue; }
        if ( (o->score() <= 0 && o->isMoved(interval_)) )
        { killObject(it); continue; }
        if ( (o->timeAlive() > interval_*300 && !o->isMoved(interval_)) )
        { killObject(it); continue; }
        if ( o->isCrashed() )
        { killObject(it); continue; }
        ++i;
        ++it;
    }
}

void Simulation::showUpdate()
{
    int i = 0;
    cout << "////////////" << endl;
    for (Objects::iterator it = objects_.begin(); it != objects_.end();)
    {
        cout << "object[" << i <<
                "]: position: " << (*it)->getPosition().x <<
                ", speed: " << (*it)->getRecentSpeed() << endl;
        ++i;
        ++it;
    }
}

void Simulation::onUpdateTimeout()
{
//    qDebug() << "Update Thread ID: " << QThread::currentThreadId();
//    qDebug() << "Update counter: " << UpdateCounter++;
    world_.Step(interval_, 8, 3);
    update();
    time_ += interval_;
    emit setTime(time_);
}

void Simulation::onCreateObjectTimeout()
{
//    qDebug() << "Create counter: " << CreateCounter++;
    createObject();

//    qDebug() << "Create elapsed time: " << elapsed_secs;
}

void Simulation::killObject(Objects::iterator &it)
{
    (*it)->calcScore();
    cout << (*it)->score() << endl;
//    qDebug() << "WORLD: Removing item[" << (*it)->id() << "]";
//    qDebug() << "Position: " << (*it)->getPosition().x << ", "
//             << (*it)->getPosition().y;
    (*it)->destroy(world_);
    genetic_.insert((*it).get());

    CarSPtr c(std::move((*it)));
    emit removeItem(c);
    objects_.erase(it);
}

void Simulation::createObject()
{
    if(!buffer_.full())
    {
        if(genetic_.full())
            buffer_.push(std::move(genetic_.create()));
        else
            buffer_.push(CarPtr(new Car(b2Vec2(initPosition_))));
    }

    if(!buffer_.empty() && (objects_.size() < buffer_.maxSize()) )
    {
        CarPtr o = buffer_.pop();
//        qDebug() << "WORLD: Adding item[" << o->id() << "]";
        bool created = o->create(world_);
        while(!created)
        {
            o.reset(new Car(b2Vec2(initPosition_)));
            created = o->create(world_);
        }

        Car *newO = o.get();
        objects_.push_back(std::move(o));

        emit addItem(newO);
    }
}
