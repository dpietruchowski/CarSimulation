#include "simulation.h"
#include <QThread>
#include <QDebug>
#include "object/car.h"
#include "object/ground.h"
#include <iostream>
#include "utilfunctions.h"

using namespace std;

const float32 Simulation::CLICKED_DISTANCE = 10;

Simulation::Simulation(b2Vec2 gravity, b2Vec2 size, size_t bufferSize,
                       const GeneticParameters& params):
    world_(gravity), ground_(size), size_(size),
    genetic_(params), buffer_(bufferSize), removed_(bufferSize)
{
    console_.setWindowFlags(Qt::WindowStaysOnTopHint);
    //console_.show();
}

void Simulation::initialize(QGraphicsScene &scene)
{
    ground_.create(world_);
    scene.addItem(&ground_);
    for(size_t i = 0; i < buffer_.maxSize(); ++i)
        buffer_.push(CarPtr(new Car(b2Vec2(10,200))));
}

void Simulation::addObject()
{
    //buffer_.print(console_,1);
    CarPtr o = buffer_.pop();
    qDebug() << "OBJECT: Adding item[" << o->id() << "]";
    objects_.push_back(std::move(o));
}

void Simulation::removeObject()
{
   // removed_.print(console_,0);
    removed_.size();
    CarPtr o = removed_.pop();
    o->destroy(world_);
    //qDebug() << "Removing item[" << o->id() << "] from world";
    genetic_.insert(std::move(o));
}

void Simulation::update()
{
    int i = 0;
    for (Objects::iterator it = objects_.begin(); it != objects_.end();)
    {
        Car *o = it->get();
        o->update(1000/60);

        float32 x = o->getPosition().x;
        o->calcScore();

        // For easy debbuging
        if ( (!o->isMoving()) )
        { killObject(it); continue; }
        if ( (x > size_.x) )
        { killObject(it); continue; }
        if ( (x < 0) )
        { killObject(it); continue; }
        if ( (o->score() <= 0 && o->isMoved()) )
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
//    qDebug() << "Update ThreadID: " << QThread::currentThreadId();
    world_.Step(1.0f/60.0f, 8, 3);
    update();
}

void Simulation::onCreateObjectTimeout()
{
//    qDebug() << "Create Object ThreadID: " << QThread::currentThreadId();
    createObject();
}

void Simulation::killObject(Objects::iterator &it)
{
    (*it)->calcScore();
    cout << (*it)->score() << endl;
    qDebug() << "Push item[" << (*it)->id() << "] to removed";
//    qDebug() << "Position: " << (*it)->getPosition().x << ", "
//             << (*it)->getPosition().y;
    removed_.push(std::move(*it));
    objects_.erase(it);

    emit removeItem(removed_.back().get());
}

void Simulation::createObject()
{
    if(!buffer_.full())
    {
        if(genetic_.full())
            buffer_.push(std::move(genetic_.create()));
        else
            buffer_.push(CarPtr(new Car(b2Vec2(10,200))));
    }

    if(!buffer_.empty() && (objects_.size() < buffer_.maxSize()) )
    {
        CarPtr &o = buffer_.front();
        qDebug() << "WORLD: Adding item[" << o->id() << "]";
        bool created = o->create(world_);
        while(!created)
        {
            o.reset(new Car(b2Vec2(10,200)));
            created = o->create(world_);
        }

        emit addItem(o.get());
    }
}
