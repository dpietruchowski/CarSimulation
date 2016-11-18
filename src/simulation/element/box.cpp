#include "box.h"
#include <math.h>
#include "utilfunctions.h"

Box::Box(float32 angle, float32 width, float32 height):
    Polygon(b2Vec2(0.f, 0.f),
            b2_staticBody,
            Qt::GlobalColor::black),
    position_(0.f, 0.f)
{
    b2Shape* shape = ShapeCreation::getPolygonShape(ShapeCreation::Vertices({initializeFirst(angle, width, height), 4}));
    addFixture(shape, Element::Parameters({10, 0.5, 0.1}));
    position_ = b2Vec2(0.f, 0.f);
}

Box::Box(const Box& box, float32 angle, float32 width):
    Polygon(box.vertices_[Corner::RIGHT_UP] + box.position_,
            b2_staticBody,
            Qt::GlobalColor::black),
    position_(box.vertices_[Corner::RIGHT_UP] + box.position_)
{
    b2Shape* shape = ShapeCreation::getPolygonShape(ShapeCreation::Vertices({calcVertices(box, angle, width), 4}));
    addFixture(shape, Element::Parameters({10, 0.5, 0.1}));
}

b2Vec2 Box::getPosition() const
{
    return position_;
}

b2Vec2 Box::getVertex(Box::Corner corner) const
{
    return vertices_.at(corner);
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
