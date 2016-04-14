#include "wheelgene.h"
#include "utilfunctions.h"
#include "simulation/element/wheel.h"

WheelGene::WheelGene(float32 radius, int vertexNumber,
                     const Element::Parameters& parameters):
    radius_(radius), vertexNumber_(vertexNumber), parameters_(parameters)
{

}

ElementPtr WheelGene::create(const b2Vec2 &position,
                             const Qt::GlobalColor &color) const
{
    return ElementPtr(new Wheel(position, radius_, color,
                                parameters_));
}

int WheelGene::getVertexNumber() const
{
    return vertexNumber_;
}

const Element::Parameters& WheelGene::getParameters() const
{
    return parameters_;
}
