#ifndef CROSSOVER_H
#define CROSSOVER_H

#include "geneticoperation.h"

class Crossover : public GeneticOperation
{
public:
    Crossover() = default;
private:
    CarPtr reproduce(const Parents &parents);
    CarPtr reproduce(const Car *parent1, const Car *parent2);
};

#endif // CROSSOVER_H
