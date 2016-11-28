#ifndef CROSSOVER_H
#define CROSSOVER_H

#include "geneticoperation.h"

class Crossover : public GeneticOperation
{
public:
    Crossover() = default;
private:
    CarPtr reproduce(const Parents &parents) const;
    virtual void addAngles(std::vector<float32> &/* unused */) const {}
    virtual CarPtr reproduce(const Car *parent1,
                             const Car *parent2) const;
};

#endif // CROSSOVER_H
