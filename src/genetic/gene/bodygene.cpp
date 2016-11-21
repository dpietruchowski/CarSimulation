#include "bodygene.h"
#include "simulation/element/polygon.h"

#include <math.h>
#include <array>
#include "utilfunctions.h"

b2Shape* BodyGene::create(const b2Vec2& vertex)
{
    std::array<b2Vec2,3> vertices;
    vertices[0] = b2Vec2(0.f, 0.f);
    vertices[1] = vertex;
    vertices[2] = vertex_;
    return ShapeCreation()(&vertices[0], 3);
}
