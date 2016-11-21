#include "wheel.h"

#include <QLineF>
#include <QTransform>
#include "utilfunctions.h"

Wheel::Wheel(const b2Vec2& position, float32 r, const Qt::GlobalColor& color,
             const Element::Parameters& parameters):
    Element(position, b2_dynamicBody, color)
{
    addFixture(ShapeCreation()(r), parameters);
}

void Wheel::drawElement(QPainter& painter,
                        const b2Vec2& position,
                        const float32 angle,
                        const b2Shape* shape) const
{

    float32 r = shape->m_radius;

    float32 angleDeg = (angle * 180) / M_PI;
    QPointF center(position.x, position.y);
    QPointF right(position.x + r, position.y);
    QLineF qLine(center, right);
    QTransform transform;
    transform = QTransform().translate(-position.x,-position.y);
    qLine = transform.map(qLine);
    transform = QTransform().rotate(angleDeg);
    qLine = transform.map(qLine);
    transform = QTransform().translate(position.x,position.y);
    qLine = transform.map(qLine);
    painter.drawEllipse(center, r, r);
    painter.drawLine(qLine);
}


