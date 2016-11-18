#include "object.h"

Object::Object(): recentSpeed_(10)
{

}

void Object::update()
{
    recentSpeed_ = 0.1 * getSpeed() + 0.9 * recentSpeed_;
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

float32 Object::getX() const
{
    return elements_[0]->getBody()->GetPosition().x;
}

float32 Object::getY() const
{
    return elements_[0]->getBody()->GetPosition().y;
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
    painter.setPen(QPen(Qt::GlobalColor::green));
    painter.drawPoint(0,0);
    painter.drawPoint(20,40);
    painter.drawPoint(20,20);
    for(const auto& g : elements_)
    {
        g->draw(painter);
    }
}
