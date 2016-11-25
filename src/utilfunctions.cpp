#include "utilfunctions.h"
#include <cmath>

b2Shape *ShapeCreation::operator()(const b2Vec2 *vertices, int32 size) const
{
    b2PolygonShape polygon;

    b2Vec2 vert[size];
    for(int i = 0; i < size; i++)
    {
        const b2Vec2* a = vertices+i;
        vert[i].Set(a->x,a->y);
    }
    polygon.Set(vert, size);

    return new b2PolygonShape(polygon);
}

b2Shape *ShapeCreation::operator()(const b2Vec2 &size) const
{
    b2PolygonShape polygon;
    polygon.SetAsBox(size.x/2, size.y/2);

    return new b2PolygonShape(polygon);
}

b2Shape *ShapeCreation::operator()(float32 r) const
{
    b2CircleShape shape;
    shape.m_radius = r;

    return new b2CircleShape(shape);
}


b2Vec2 VertexCalculation::operator()(const b2Vec2 &vertex, float32 angle,
                                     float32 length) const
{
    return calcVertex(b2Vec2(0, 0), vertex, angle, length);
}

b2Vec2 VertexCalculation::calcVertex(const b2Vec2& centerVertex,
                                     const b2Vec2& vertex2,
                                     float32 angle,
                                     float32 length) const
{
    b2Vec2 rotatePoint = calcPoint(centerVertex, vertex2,
                            angle);
    rotatePoint.x += centerVertex.x;
    rotatePoint.y += centerVertex.y;
    b2Vec2 line = calcLine(centerVertex, rotatePoint);

    return calcPointInLine(line, centerVertex, length, isOnRight(centerVertex,
                                                                 rotatePoint));
}


b2Vec2 VertexCalculation::calcPoint(const b2Vec2& point, float32 angle) const
{
    b2Vec2 rPoint;

    angle = (angle * M_PI) / 180.f;

    rPoint.x = point.x * cos(angle)
            - point.y * sin(angle);

    rPoint.y = point.x * sin(angle)
            + point.y * cos(angle);

    return rPoint;
}

b2Vec2 VertexCalculation::calcPoint(const b2Vec2& centerPoint,
                                    const b2Vec2& rotatePoint,
                                    float32 angle) const
{
    b2Vec2 point;
    point.x = rotatePoint.x - centerPoint.x;
    point.y = rotatePoint.y - centerPoint.y;

    return calcPoint(point, angle);
}

b2Vec2 VertexCalculation::calcLine(const b2Vec2& point1, const b2Vec2& point2) const
{
    b2Vec2 line;

    //x -- a
    //y -- b
    line.x = (point2.y - point1.y) / (point2.x - point1.x);
    line.y = (point2.x*point1.y - point1.x*point2.y)
             / (point2.x - point1.x);

    return line;
}

b2Vec2 VertexCalculation::calcPointInLine(const b2Vec2& line,
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

float32 AngleCalculation::operator()(const b2Vec2 &point1, const b2Vec2 &point2)
{
    return (*this)(point2) - (*this)(point1);
}

float32 AngleCalculation::operator()(const b2Vec2 &point)
{
    if(point.y < 0)
        return 360 + atan2(point.y, point.x)*(180/M_PI);
    return atan2(point.y, point.x)*(180/M_PI);
}
