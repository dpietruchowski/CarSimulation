#include "crossover.h"

CarPtr Crossover::reproduce(const GeneticOperation::Parents &parents) const
{
    if(parents.size() != 2)
        throw "Missing parent";

    return reproduce(parents[0], parents[1]);
}

CarPtr Crossover::reproduce(const Car *parent1, const Car *parent2) const
{
    std::vector<float32> angles;
    addAngles(angles);

    return CarPtr(new Car(*parent1, *parent2, angles));
}
