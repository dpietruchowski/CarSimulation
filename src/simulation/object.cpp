#include "object.h"

Object::Object()
{

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
