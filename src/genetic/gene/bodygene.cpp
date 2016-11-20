#include "bodygene.h"
#include "simulation/element/polygon.h"

#include <math.h>
#include <array>
#include "utilfunctions.h"

BodyGene::BodyGene(float32 angle, float32 length,
                   const Element::Parameters& parameters):
    angle_(angle), length_(length), parameters_(parameters)
{
}

b2Shape* BodyGene::create(const b2Vec2& vertex)
{
    std::array<b2Vec2,3> vertices;
    vertices[0] = b2Vec2(0.f, 0.f);
    vertices[1] = vertex;
    vertices[2] = calcVertex(vertices[0], vertex, angle_, length_);
    vertex_ = vertices[2];
    return ShapeCreation::getPolygonShape(ShapeCreation::Vertices({&vertices[0], 3}));
}

const b2Vec2& BodyGene::getVertex() const
{
    return vertex_;
}

const Element::Parameters& BodyGene::getParameters() const
{
    return parameters_;
}

b2Vec2 BodyGene::calcVertex(const b2Vec2& centerVertex,
                             const b2Vec2& vertex2,
                             float32 angle,
                             float32 length) const
{
    b2Vec2 rotatePoint = calcPoint(centerVertex, vertex2,
                            angle);
    rotatePoint.x += centerVertex.x;
    rotatePoint.y += centerVertex.y;
    b2Vec2 line = calcLine(centerVertex, rotatePoint);

    return calcPointInLine(line, centerVertex, length,
                                  isOnRight(centerVertex,
                                            rotatePoint));
}


b2Vec2 BodyGene::calcPoint(const b2Vec2& point, float32 angle) const
{
    b2Vec2 rPoint;

    angle = (angle * M_PI) / 180.f;

    rPoint.x = point.x * cos(angle)
            - point.y * sin(angle);

    rPoint.y = point.x * sin(angle)
            + point.y * cos(angle);

    return rPoint;
}

b2Vec2 BodyGene::calcPoint(const b2Vec2& centerPoint,
                           const b2Vec2& rotatePoint,
                           float32 angle) const
{
    b2Vec2 point;
    point.x = rotatePoint.x - centerPoint.x;
    point.y = rotatePoint.y - centerPoint.y;

    return calcPoint(point, angle);
}

b2Vec2 BodyGene::calcLine(const b2Vec2& point1, const b2Vec2& point2) const
{
    b2Vec2 line;

    //x -- a
    //y -- b
    line.x = (point2.y - point1.y)/(point2.x - point1.x);
    line.y = (point2.x*point1.y - point1.x*point2.y)
            /(point2.x - point1.x);

    return line;
}

bool BodyGene::isOnRight(const b2Vec2& centerPoint,
                         const b2Vec2& rotatePoint) const
{
    return rotatePoint.x > centerPoint.x;
}

b2Vec2 BodyGene::calcPointInLine(const b2Vec2& line,
                                 const b2Vec2& point,
                                 float32 length,
                                 bool onRight) const
{
    b2Vec2 rPoint;

    float32 coeff = length / sqrt(1 + line.x* line.x);
    if(onRight)
        rPoint.x = point.x + coeff;
    else
        rPoint.x = point.x - coeff;

    rPoint.y = line.x * rPoint.x + line.y;

    return rPoint;
}
