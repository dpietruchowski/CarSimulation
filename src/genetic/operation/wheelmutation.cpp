#include "wheelmutation.h"

GeneticOperation *WheelMutation::create()
{
    return new WheelMutation();
}

CarPtr WheelMutation::reproduce(const Car *parent) const
{
    Element::Parameters param = Element::Parameters::createRandom();
    int max = WheelGene::MAX_RADIUS;
    int min = 1;
    float32 radius = (double)std::rand() / RAND_MAX;;
    radius *= (max - min);
    radius += min;
    size_t index = std::rand() % parent->bodySize();
    WheelGene gene(radius, index, param);

    return CarPtr(new Car(*parent, gene, std::rand() % 2));
}
