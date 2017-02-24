#include "object.h"
#include <qcompilerdetection.h>
#include <iostream>
#include "car.h"

using namespace std;

oid Object::ID_ = 0;

Object::Object(): recentSpeed_(10)
{
    id_ = ID_++;
}

Object::Object(const Object &other): QGraphicsItem(),
    recentSpeed_(10), id_(other.id_)
{
}

void Object::initialize()
{
    initialize(elements_);
}

void Object::update(double interval)
{
    recentSpeed_ = 0.1 * getSpeed() + 0.9 * recentSpeed_;
    updateObject(interval);
}

bool Object::create(b2World &world)
{
    if(!canBeCreated())
        return false;

    initialize(elements_);

    for(const auto& g : elements_)
    {
        g->create(world);
    }
    createJoints(elements_, world);

    return true;
}

void Object::destroy(b2World &world)
{
    for(const auto& g : elements_)
    {
        world.DestroyBody(g->getBody());
    }
}

const b2Vec2 &Object::getPosition() const
{
    return elements_[0]->getBody()->GetPosition();
}

float32 Object::getSpeedX() const
{
    return elements_[0]->getBody()->GetLinearVelocity().x;
}

float32 Object::getSpeedY() const
{
    return elements_[0]->getBody()->GetLinearVelocity().y;
}

float32 Object::getSpeed() const
{
    return elements_[0]->getBody()->GetLinearVelocity().Length();
}

bool Object::isMoving() const
{
    return recentSpeed_ > 2;
}

float32 Object::getRecentSpeed() const
{
    return recentSpeed_;
}

oid Object::id() const
{
    return id_;
}

void Object::advance(int phase)
{
    if(!phase) return;

    setPos(getPosition().x, getPosition().y);
}

void Object::drawId(QPainter *painter) const
{
    QString text("n");
    const Car* c = dynamic_cast<const Car*>(this);
    if(dynamic_cast<const Car*>(this)) {
        //const_cast<Car*> (c)->calcScore();
        text = QString::number(id_);
    }

    //text = QString::number(id_);
    QFont myFont;
    myFont.setPointSizeF(1.0);
    myFont.setPixelSize(5);
    myFont.setFamily("Courier");
    painter->setFont(myFont);
    QTransform transform = painter->transform();
    transform.scale(1, -1);
    painter->setTransform(transform);
    painter->drawText(QPointF(0,-10), text);
    transform.scale(1, -1);
    painter->setTransform(transform);
}

void Object::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *,
                   QWidget *)
{
    drawId(painter);
    for(const auto& g : elements_)
    {
        b2Vec2 position;
        position.x = static_cast<float32> (pos().x());
        position.y = static_cast<float32> (pos().y());
        g->draw(*painter, position);
    }
}

void Object::showPos()
{
    cout << "/////" << endl;
    for(const auto& g : elements_)
    {
        cout << "x: " << g->getBody()->GetPosition().x
             << " y: " << g->getBody()->GetPosition().y << endl;
    }
}
