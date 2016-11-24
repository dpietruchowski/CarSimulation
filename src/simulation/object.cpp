#include "object.h"

Object::Object(): recentSpeed_(10)
{

}

void Object::update(double interval)
{
    recentSpeed_ = 0.1 * getSpeed() + 0.9 * recentSpeed_;
    updateObject(interval);
}

void Object::create(b2World &world)
{
    initialize(elements_);

    for(const auto& g : elements_)
    {
        g->create(world);
    }
    createJoints(elements_, world);
}

void Object::destroy(b2World &world)
{
    for(const auto& g : elements_)
    {
        g->destroy(world);
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
    return recentSpeed_ > 2.5f;
}

void Object::draw(QPainter &painter) const
{
    for(const auto& g : elements_)
    {
        g->draw(painter);
    }
}
