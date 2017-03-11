#include "bodygene.h"
#include "simulation/element/polygon.h"

#include <array>
#include "utilfunctions.h"

BodyGene::BodyGene(const Element::Parameters &parameters, const b2Vec2 &vertex):
    Gene(parameters), vertex_(vertex)
{
}

b2Shape* BodyGene::create(const b2Vec2& vertex)
{
    std::array<b2Vec2,3> vertices;
    vertices[0] = b2Vec2(0.f, 0.f);
    vertices[1] = vertex;
    vertices[2] = vertex_;
    return ShapeCreation()(&vertices[0], 3);
}

const b2Vec2 &BodyGene::getVertex() const
{
    return vertex_;
}

void BodyGene::geneToString(std::string &gene) const
{
    gene += std::to_string(vertex_.x) + " ";
    gene += std::to_string(vertex_.y) + " ";
}
