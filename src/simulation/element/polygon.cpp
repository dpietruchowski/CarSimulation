#include "polygon.h"
#include <iostream>
#include <array>
#include <math.h>
#include <QVector>
#include <QPolygonF>
#include <QPointF>
#include <QTransform>
#include <utilfunctions.h>

using namespace std;

Polygon::Polygon(const b2Vec2& position, b2Shape* shape,
                 const b2BodyType& bodyType,
                 const Qt::GlobalColor& color):
    Element(position, bodyType, color)
{
    addFixture(shape);
}

Polygon::Polygon(const b2Vec2& position,
                 const b2BodyType& bodyType,
                 const Qt::GlobalColor& color):
     Element(position, bodyType, color)
{
//    addFixture(ShapeCreation::getPolygonShape(b2Vec2(10,10)));
}

void Polygon::drawElement(QPainter &painter,
                          const b2Vec2 &position,
                          const float32 angle,
                          const b2Shape* shape,
                          const b2Vec2& parentPosition) const
{
    const b2PolygonShape* polygon = dynamic_cast<const b2PolygonShape*>(shape);
    int count = static_cast<int>(polygon->GetVertexCount());

    QVector<QPointF> points;
    for(int i = 0; i < count; i++)
    {
        b2Vec2 p = polygon->GetVertex(i);
        QPointF point(p.x, p.y);
        points.push_back(point);
    }

    //TODO add comment what happens here
    float32 angleDeg = (angle * 180) / M_PI;
    QPolygonF qPolygon(points);
    QTransform transform;
    transform = QTransform().rotate(angleDeg);
    qPolygon = transform.map(qPolygon);

    painter.drawPolygon(qPolygon);
}
