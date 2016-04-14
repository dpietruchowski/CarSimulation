#include "box.h"
#include <math.h>
#include "utilfunctions.h"

Box::Box(float32 angle, float32 width, float32 height):
    Polygon(b2Vec2(0.f, 0.f),
            b2_staticBody,
            Qt::GlobalColor::black)
{
    b2Shape* shape = ShapeCreation::getPolygonShape(ShapeCreation::Vertices({initializeFirst(angle, width, height), 4}));
    addFixture(shape, Element::Parameters({10, 0.5, 0.1}));
    position_ = b2Vec2(0.f, 0.f);
}

Box::Box(const Box& box, float32 angle, float32 width):
    Polygon(box.vertices_[2] + box.position_,
            b2_staticBody,
            Qt::GlobalColor::black)
{
    b2Shape* shape = ShapeCreation::getPolygonShape(ShapeCreation::Vertices({calcVertices(box, angle, width), 4}));
    addFixture(shape, Element::Parameters({10, 0.5, 0.1}));
    position_ = box.vertices_[2] + box.position_;
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
    b2Vec2 upEndPoint = calcPoint(box.vertices_[2],
                                  angle, width);
    b2Vec2 downEndPoint = calcPoint(box.vertices_[3],
                                    angle, width);

    vertices_[0] = box.vertices_[2];
    vertices_[1] = box.vertices_[3];
    vertices_[2] = upEndPoint;
    vertices_[3] = downEndPoint;

    position_ = box.vertices_[2] + box.position_;

    for(auto& v: vertices_)
    {
        v -= position_;
        v += box.position_;
    }

    return &vertices_[0];
}

b2Vec2* Box::initializeFirst(float32 angle,
                             float32 width,
                             float32 height)
{
    vertices_[0] = b2Vec2(0.f, 0.f);
    vertices_[1] = b2Vec2(0.f, -height);
    vertices_[2] = b2Vec2(0.f, 0.f);
    vertices_[3] = b2Vec2(0.f, -height);

    return calcVertices(*this,
                        angle,
                        width);
}
