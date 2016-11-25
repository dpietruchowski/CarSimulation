#ifndef WHEELGENE_H
#define WHEELGENE_H

#include "simulation/object.h"

class WheelGene
{
public:
    static const int MAX_RADIUS = 4;
public:
    WheelGene(float32 radius, size_t vertexNumber,
              const Element::Parameters& parameters);
    WheelGene(const WheelGene &other, size_t maxVertexNumber);
    WheelGene(const WheelGene &other) = default;

    /// Create wheel element using to simulation
    ElementPtr create(const b2Vec2& position,
                      const Qt::GlobalColor& color) const;

    /// Return vertice number in car body,
    /// with whom wheel creates joint
    size_t getVertexNumber() const;
    const Element::Parameters& getParameters() const;
    std::string toString() const;

private:
    float32 radius_;
    /// Vertex number in car body, with whom wheel creates joint
    size_t vertexNumber_;
    Element::Parameters parameters_;

};

#endif // WHEELGENE_H
