#include "crossover.h"

CarPtr Crossover::reproduce(const GeneticOperation::Parents &parents)
{
    if(parents.size() != 2)
        throw "Missing parent";

    return reproduce(parents[0], parents[1]);
}

CarPtr Crossover::reproduce(const Car *parent1, const Car *parent2)
{
    std::vector<float32> angles;
    angles.push_back(90);
    angles.push_back(180);
    angles.push_back(270);
    angles.push_back(360);

    return CarPtr(new Car(*parent1, *parent2, angles));
}
