#include "wheel.h"

#include <QLineF>
#include <QTransform>
#include "utilfunctions.h"
#include <iostream>

using namespace std;

Wheel::Wheel(const b2Vec2& position, float32 r, const Qt::GlobalColor& color,
             const Element::Parameters& parameters):
    Element(position, b2_dynamicBody, color)
{
    addFixture(ShapeCreation()(r), parameters);
}

Element *Wheel::clone() const
{
   return new Wheel(*this);
}

void Wheel::drawElement(QPainter &painter,
                        const b2Vec2 &position,
                        const float32 angle,
                        const b2Shape *shape,
                        const b2Vec2 &parentPosition) const
{
    float32 r = shape->m_radius;
    b2Vec2 pos = position - parentPosition;

    float32 angleDeg = (angle * 180) / M_PI;
    QPointF center(pos.x, pos.y);
    QPointF right(pos.x + r, pos.y);
    QLineF qLine(center, right);
    QTransform transform;
    transform = QTransform().translate(-pos.x,-pos.y);
    qLine = transform.map(qLine);
    transform = QTransform().rotate(angleDeg);
    qLine = transform.map(qLine);
    transform = QTransform().translate(pos.x,pos.y);
    qLine = transform.map(qLine);

    painter.drawEllipse(center, r, r);
    painter.drawLine(qLine);
}


