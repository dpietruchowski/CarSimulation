#include "object.h"
#include <qcompilerdetection.h>
#include <iostream>

using namespace std;

Object::Object(): recentSpeed_(10)
{

}

void Object::update(double interval)
{
    recentSpeed_ = 0.1 * getSpeed() + 0.9 * recentSpeed_;
    updateObject(interval);
}

QRectF Object::boundingRect() const
{
    b2Vec2 position = getPosition();
    return QRectF(position.x-500, position.y-500, 10000, 10000);
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
    return recentSpeed_ > 2.0f;
}

float32 Object::getRecentSpeed() const
{
    return recentSpeed_;
}

void Object::advance(int phase)
{
    if(!phase) return;

    setPos(getPosition().x, getPosition().y);
}

void Object::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *,
                   QWidget *)
{
    for(const auto& g : elements_)
    {
        g->draw(*painter, getPosition());
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
