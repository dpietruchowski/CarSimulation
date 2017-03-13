#include "box.h"
#include <math.h>
#include <iostream>
#include <utility>
#include "utilfunctions.h"

using namespace std;

Box::Box(float32 angle, float32 width, float32 height):
    Polygon(b2Vec2(0.f, 0.f),
            b2_staticBody,
            Qt::GlobalColor::black),
    position_(0.f, 0.f)
{
    b2Shape* shape = ShapeCreation()(initializeFirst(angle, width, height), 4);
    addFixture(shape, Element::Parameters({10, 1, 0.1}));
    position_ = b2Vec2(0.f, 0.f);
}

Box::Box(const Box& box, float32 angle, float32 width):
    Polygon(box.vertices_[Corner::RIGHT_UP] + box.position_,
            b2_staticBody, Qt::GlobalColor::black),
    position_(box.vertices_[Corner::RIGHT_UP] + box.position_)
{
    b2Shape* shape = ShapeCreation()(calcVertices(box, angle, width), 4);
    addFixture(shape, Element::Parameters({10, 1, 0.1}));
}

Box &Box::operator=(const Box &other)
{
    if(&other == this)
        return *this;

    Box copy(other);
    swap(copy);

    return *this;
}

Element *Box::clone() const
{
    return new Box(*this);
}

b2Vec2 Box::getPosition() const
{
    return position_;
}

b2Vec2 Box::getVertex(Box::Corner corner) const
{
    return vertices_.at(corner);
}

void Box::swap(Box &other)
{
    Element::swap(other);
    std::swap(position_, other.position_);
    vertices_.swap(other.vertices_);
}

b2Vec2 Box::calcPoint(b2Vec2 startPoint,
                      float32 angle,
                      float32 width) const
{
    if(angle > 90)
        throw "Za duzy kat";

    angle = (angle * M_PI) / 180.f;
    float32 dx, dy;
    dx = cos(angle) * width;
    dy = sin(angle) * width;
    return b2Vec2(startPoint.x + dx,
                  startPoint.y + dy);
}

b2Vec2* Box::calcVertices(const Box& box,
                          float32 angle,
                          float32 width)
{
    b2Vec2 upEndPoint = calcPoint(box.vertices_[Corner::RIGHT_UP],
                                  angle, width);
    b2Vec2 downEndPoint = calcPoint(box.vertices_[RIGHT_DOWN],
                                    angle, width);

    vertices_[Corner::LEFT_UP] = box.vertices_[Corner::RIGHT_UP];
    vertices_[Corner::LEFT_DOWN] = box.vertices_[RIGHT_DOWN];
    vertices_[Corner::RIGHT_UP] = upEndPoint;
    vertices_[Corner::RIGHT_DOWN] = downEndPoint;

    position_ = box.vertices_[Corner::RIGHT_UP] + box.position_;

    for(auto& v: vertices_)
    {
        v -= position_;
        v += box.position_;
    }

    return &vertices_[Corner::LEFT_UP];
}

b2Vec2* Box::initializeFirst(float32 angle,
                             float32 width,
                             float32 height)
{
    vertices_[Corner::LEFT_UP] = b2Vec2(0.f, 0.f);
    vertices_[Corner::LEFT_DOWN] = b2Vec2(0.f, -height);
    vertices_[Corner::RIGHT_UP] = b2Vec2(0.f, 0.f);
    vertices_[Corner::RIGHT_DOWN] = b2Vec2(0.f, -height);

    return calcVertices(*this,
                        angle,
                        width);
}

void Box::drawElement(QPainter &painter,
                      const b2Vec2 &position,
                      const float32 angle,
                      const b2Shape *shape,
                      const b2Vec2 &/* parentPosition */) const
{
    const b2PolygonShape* polygon = dynamic_cast<const b2PolygonShape*>(shape);
    int count = static_cast<int>(polygon->GetVertexCount());

    QVector<QPointF> points;
    for(int i = 0; i < count; i++)
    {
        b2Vec2 p = polygon->GetVertex(i);
        QPointF point(position.x + p.x, position.y + p.y);
        points.push_back(point);
    }

    //TODO add comment what happens here
    float32 angleDeg = (angle * 180) / M_PI;
    QPolygonF qPolygon(points);
    QTransform transform;
    transform = QTransform().translate(-position.x, -position.y);
    qPolygon = transform.map(qPolygon);
    transform = QTransform().rotate(angleDeg);
    qPolygon = transform.map(qPolygon);
    transform = QTransform().translate(position.x, position.y);
    qPolygon = transform.map(qPolygon);

    painter.drawPolygon(qPolygon);
}
