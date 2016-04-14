#include "world.h"
#include "car.h"
#include "ground.h"
#include <iostream>

using namespace std;

World::World(b2Vec2 gravity, QWidget *parent) :
    QWidget(parent), world_(gravity), timerId_(0)
{
    transform_.scale(3.0f, -3.0f);
    transform_.translate(10.0f, -40.0f);
    mousePressed_ = false;
    oldPosition_ = QPoint(0,0);

    objects_.push_back(new Ground());
    objects_.push_back(new Car(b2Vec2(10,20)));
    objects_.push_back(new Car(b2Vec2(10,30)));
    objects_.push_back(new Car(b2Vec2(10,10)));
    Object* o = objects_[0];
    o->create(world_);
    o = objects_[1];
    o->create(world_);
    o = objects_[2];
    o->create(world_);
    o = objects_[3];
    o->create(world_);
}

void World::start()
{
    if(!timerId_)
    {
        timerId_ = startTimer(1000/60); // 60fps
    }
}


void World::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == timerId_)
    {
        world_.Step(1.0f/60.0f, 8, 3);
        update();
    }
}

void World::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setTransform(transform_);
    //p.drawEllipse(20,20,10,10);
    for(auto& o : objects_)
    {
        o->draw(p);
    }
    p.setPen(QPen(Qt::GlobalColor::yellow,0.2));
    p.drawPoint(QPointF(0,0));
    p.drawPoint(QPointF(10,0));
    p.drawPoint(QPointF(10,10));
    p.drawPoint(QPointF(0,10));
}

void World::mousePressEvent(QMouseEvent* event)
{
    mousePressed_ = true;
    oldPosition_ = event->pos();
}

void World::mouseReleaseEvent(QMouseEvent* event)
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
    }
}
