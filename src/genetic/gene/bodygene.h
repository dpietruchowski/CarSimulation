#ifndef BODYGENE_H
#define BODYGENE_H

#include "gene.h"

/**
 * @brief The BodyGene class contains information about body's part
 * as angle, length, parameters (friction, density, restitution), and vertice,
 * which is shared with other part of body. One vertex is center of car body
 * and commond for all parts.
 */

class BodyGene
{
public:
    static const int MAX_LENGTH = 8;
    static const int MIN_LENGTH = 2;
public:
    BodyGene(const Element::Parameters& parameters, const b2Vec2 &vertex):
        parameters_(parameters), vertex_(vertex) {}
    BodyGene(const BodyGene &other) = default;

    /// Create polygon shape as triangle with vertices:
    /// First vertex is center of car's body and this is position of car
    /// Second vertex is shared with previous part of body
    /// Third vertex is calculated and shared with next part of body
    b2Shape* create(const b2Vec2& vertex);

    const Element::Parameters& getParameters() const { return parameters_; }
    const b2Vec2& getVertex() const { return vertex_; }

    std::string toString() const;

private:
    Element::Parameters parameters_;
    b2Vec2 vertex_;
};

#endif // BODYGENE_H
