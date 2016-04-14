#ifndef UTILFUNCTIONS
#define UTILFUNCTIONS

#include <Box2D/Box2D.h>

#endif // UTILFUNCTIONS

namespace ShapeCreation
{
    /// Vertices array with number of vertices
    struct Vertices
    {
        b2Vec2* vertices;
        int32 size;
    };

    /// Create polygon shape with vertices on heap
    b2Shape* getPolygonShape(const Vertices& vertices);
    /// Create polygon shape and set is as box with size on heap
    b2Shape* getPolygonShape(const b2Vec2& size);
    /// Create circle shape of radius size r on heap
    b2Shape* getCircleShape(float32 r);
}
