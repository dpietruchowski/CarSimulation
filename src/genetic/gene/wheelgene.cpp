#include "wheelgene.h"
#include "utilfunctions.h"
#include "simulation/element/wheel.h"

WheelGene::WheelGene(float32 radius, size_t vertexNumber,
                     const Element::Parameters& parameters):
    Gene(parameters), radius_(radius), vertexNumber_(vertexNumber)
{
}

WheelGene::WheelGene(const WheelGene &other, size_t maxVertexNumber):
    WheelGene(other)
{
    vertexNumber_ = vertexNumber_ < maxVertexNumber ?
                vertexNumber_ : maxVertexNumber - 1;
}

bool WheelGene::operator==(const WheelGene &other) const
{
    return vertexNumber_ == other.vertexNumber_;
}

bool WheelGene::operator!=(const WheelGene &other) const
{
    return !(*this == other);
}

ElementPtr WheelGene::create(const b2Vec2 &position,
                             const Qt::GlobalColor &color) const
{
    return ElementPtr(new Wheel(position, radius_, color, getParameters()));
}

size_t WheelGene::getVertexNumber() const
{
    return vertexNumber_;
}

void WheelGene::geneToString(std::string &gene) const
{
    gene += std::to_string(radius_) + " ";
    gene += std::to_string(vertexNumber_) + " ";
}
