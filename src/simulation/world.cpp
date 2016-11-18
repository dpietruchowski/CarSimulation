#include "world.h"
#include "car.h"
#include "ground.h"
#include <iostream>

using namespace std;

World::World(b2Vec2 gravity, b2Vec2 size, QWidget *parent) :
    QWidget(parent), world_(gravity), timerId_(0), secTimerId_(0), size_(size)
{
    transform_.scale(5.0f, -5.0f);
    transform_.translate(10.0f, -40.0f);
    mousePressed_ = false;
    oldPosition_ = QPoint(0,0);

    ground_ = new Ground(size_);
    ground_->create(world_);
    objects_.push_back(new Car(b2Vec2(10,200)));
//    o = objects_[1];
    Object* o = objects_[0];
    o->create(world_);
}

void World::start()
{
    if(!timerId_)
    {
        timerId_ = startTimer(1000/60); // 60fps
    }
    if(!secTimerId_)
    {
        secTimerId_ = startTimer(1000); // 60fps
    }
}

void World::myUpdate()
{
    int i = 0;
    for (Objects_::iterator it = objects_.begin(); it != objects_.end(); ++it)
    {
        Object *o = *it;
        cout << "x: " << o->getX() << endl;
        cout << "y: " << o->getY() << endl;
        cout << "predkosc: " << o->getSpeed() << endl;
        string moving = o->isMoving() ? "jedzie" : "stoi";
        cout << moving << endl;
        o->update();

        if ( (!o->isMoving()) || (o->getX() > size_.x) || (o->getX() < 0) )
        {
            cout << i << endl;
            o->destroy(world_);
            objects_.erase(it);
            --it;
        }
        ++i;
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
            Object* o = new Car(b2Vec2(10,200));
            o->create(world_);
            objects_.push_back(o);
        }
    }
}

void World::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setTransform(transform_);
    //p.drawEllipse(20,20,10,10);
    ground_->draw(p);
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
