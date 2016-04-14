#include "utilfunctions.h"

b2Shape* ShapeCreation::getPolygonShape(const Vertices& vertices)
{
    b2PolygonShape polygon;
    int32 count = vertices.size;

    b2Vec2 vert[vertices.size];
    for(int i = 0; i < vertices.size; i++)
    {
        b2Vec2* a = vertices.vertices+i;
        vert[i].Set(a->x,a->y);
    }
    polygon.Set(vert, count);

    return new b2PolygonShape(polygon);
}

b2Shape* ShapeCreation::getPolygonShape(const b2Vec2& size)
{
    b2PolygonShape polygon;
    polygon.SetAsBox(size.x/2, size.y/2);

    return new b2PolygonShape(polygon);
}

b2Shape* ShapeCreation::getCircleShape(float32 r)
{
    b2CircleShape shape;
    shape.m_radius = r;

    return new b2CircleShape(shape);
}
