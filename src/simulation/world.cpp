#include "world.h"
#include "car.h"
#include "ground.h"
#include <iostream>
#include "utilfunctions.h"

using namespace std;

const float32 World::CLICKED_DISTANCE = 10;

World::World(b2Vec2 gravity, b2Vec2 size, QWidget *parent) :
    QWidget(parent), world_(gravity), timerId_(0), secTimerId_(0),
    ground_(size), size_(size), genetic_(50, SelectionType::RANK_ROULETTESELECTION),
    interval_(1000/600)
{
    transform_.scale(5.0f, -5.0f);
    transform_.translate(10.0f, -40.0f);
    mousePressed_ = false;
    oldPosition_ = QPoint(0,0);

    ground_.create(world_);
    objects_.push_back(CarPtr(new Car(b2Vec2(10,200))));
    Car* o = objects_[0].get();
    o->create(world_);
    for(int i = 0; i < 50; ++i)
        genetic_.insert(CarPtr(new Car(*o)));
}

void World::start()
{
    if(!timerId_)
    {
        timerId_ = startTimer(interval_); // 60fps
    }
    if(!secTimerId_)
    {
        secTimerId_ = startTimer(400); // 60fps
    }
}

void World::myUpdate()
{
    float32 minDistance = size_.Length();
    Objects_::iterator nearestIt;
    int i = 0;
    for (Objects_::iterator it = objects_.begin(); it != objects_.end();)
    {
        Car *o = it->get();
        o->update(interval_);

        float32 x = o->getPosition().x;
        if ( (!o->isMoving()) || (x > size_.x) || (x < 0) )
        {
            o->calcScore();
            o->destroy(world_);
            genetic_.insert(std::move(*it));
            objects_.erase(it);
            continue;
        }

        b2Vec2 diffPosition = clickedPosition_ - o->getPosition();
        float32 distance = diffPosition.Length();
        if(distance < minDistance)
        {
            minDistance = distance;
            nearestIt = it;
        }

        ++i;
        ++it;
    }

    if( (minDistance < CLICKED_DISTANCE) && mousePressed_ )
    {
        (*nearestIt)->calcScore();
        (*nearestIt)->destroy(world_);
        genetic_.insert(std::move(*nearestIt));
        objects_.erase(nearestIt);
    }
}


void World::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == timerId_)
    {
        world_.Step(1.0f/60.0f, 8, 3);
        update();
        myUpdate();
    }
    if(event->timerId() == secTimerId_)
    {
        if(objects_.size() < 30)
        {
            CarPtr o = genetic_.create();
            o->create(world_);
            objects_.push_back(std::move(o));
        }
    }
}

void World::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setTransform(transform_);
    ground_.draw(p);
    for(auto& o : objects_)
    {
        o->draw(p);
    }
    p.setPen(QPen(Qt::GlobalColor::red,1));
    p.drawPoint(QPointF(0,0));
    p.setPen(QPen(Qt::GlobalColor::blue,0.1));
    p.drawLine(QPointF(-10,0), QPointF(size_.x,0));
    p.drawLine(QPointF(0,-size_.y/2), QPointF(0,size_.y/2));
    p.drawLine(QPointF(size_.x,-size_.y/2), QPointF(size_.x,size_.y/2));
}

void World::mousePressEvent(QMouseEvent* event)
{
    mousePressed_ = true;
    oldPosition_ = event->pos();
    updateClickedPosition();
}

void World::mouseReleaseEvent(QMouseEvent*)
{
    mousePressed_ = false;
}

void World::mouseMoveEvent(QMouseEvent* event)
{
    if(mousePressed_)
    {
        const QPointF delta = event->pos() - oldPosition_;
        transform_.translate(delta.x()/3, -delta.y()/3);
        oldPosition_ = event->pos();
        updateClickedPosition();
    }
}

void World::updateClickedPosition()
{
    qreal dx = transform_.dx();
    qreal dy = transform_.dy();
    qreal sx = transform_.m11();
    qreal sy = transform_.m22();
    clickedPosition_.x = static_cast<float32> (oldPosition_.x() - dx) / sx;
    clickedPosition_.y = static_cast<float32> (oldPosition_.y() - dy) / sy;
}
