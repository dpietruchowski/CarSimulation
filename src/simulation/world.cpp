#include "world.h"
#include "car.h"
#include "ground.h"
#include <iostream>
#include "utilfunctions.h"

using namespace std;

const float32 World::CLICKED_DISTANCE = 10;

World::World(b2Vec2 gravity, b2Vec2 size, QWidget *parent) :
    QGraphicsScene(parent), world_(gravity), ground_(size), size_(size),
    genetic_(30, SelectionType::RANK_ROULETTESELECTION),
    interval_(1000.0/60), buffer_(30), worldTimerId_(0), createTimerId_(0),
    drawTimerId_(0)
{
    ground_.create(world_);
    addItem(&ground_);
    objects_.push_back(CarPtr(new Car(b2Vec2(10,30))));
    Car* o = objects_[0].get();
    addItem(o);
    o->create(world_);
    for(int i = 0; i < 30; ++i)
        buffer_.push(CarPtr(new Car(b2Vec2(10,200))));
}

void World::start()
{
    killTimer(worldTimerId_);
    worldTimerId_ = 0;
    if(!worldTimerId_)
    {
        worldTimerId_ = startTimer(interval_);
    }
    killTimer(createTimerId_);
    createTimerId_ = 0;
    if(!createTimerId_)
    {
        createTimerId_ = startTimer(interval_ * 30);
    }
    if(!drawTimerId_)
    {
        drawTimerId_ = startTimer(1000/60);
    }
}

void World::stop()
{

    killTimer(worldTimerId_);
    killTimer(createTimerId_);
}

void World::myUpdate()
{
    int i = 0;
    for (Objects_::iterator it = objects_.begin(); it != objects_.end();)
    {
        Car *o = it->get();
        o->update(interval_);

        float32 x = o->getPosition().x;
        o->calcScore();
        if ( (!o->isMoving())
             || (x > size_.x)
             || (x < 0)
             || (o->score() <= 0 && o->isMoved()) )
        {
            killObject(it);
            continue;
        }
        ++i;
        ++it;
    }
}

void World::showUpdate()
{
    int i = 0;
    cout << "////////////" << endl;
    for (Objects_::iterator it = objects_.begin(); it != objects_.end();)
    {
        cout << "object[" << i <<
                "]: position: " << (*it)->getPosition().x <<
                ", speed: " << (*it)->getRecentSpeed() << endl;
        ++i;
        ++it;
    }
}


void World::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == drawTimerId_)
    {
        advance();
        //showUpdate();
    }
    if(event->timerId() == worldTimerId_)
    {
        world_.Step(1.0f/60.0f, 8, 3);
        myUpdate();
    }
    if(event->timerId() == createTimerId_)
    {
        createObject();
    }
}

void World::forward(bool toggled)
{
    if(toggled)
        interval_ = 1000.0/600;
    else
        interval_ = 1000.0/60;
    start();
}

void World::killObject(Objects_::iterator &it)
{
    (*it)->calcScore();
    (*it)->destroy(world_);
    cout << (*it)->score() << endl;
    removeItem((*it).get());
    genetic_.insert(std::move(*it));
    objects_.erase(it);
}

void World::createObject()
{
    if(!buffer_.full())
    {
        if(genetic_.full())
            buffer_.push(std::move(genetic_.create()));
        else
            buffer_.push(CarPtr(new Car(b2Vec2(10,200))));
    }

    if(!buffer_.empty() && (objects_.size() < 30) )
    {
        CarPtr o = buffer_.pop();
        bool created = o->create(world_);
        while(!created)
        {
            o = CarPtr(new Car(b2Vec2(10,200)));
            created = o->create(world_);
        }
        addItem(o.get());
        objects_.push_back(std::move(o));
    }
}
