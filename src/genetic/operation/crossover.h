#ifndef CROSSOVER_H
#define CROSSOVER_H

#include "geneticoperation.h"

class Crossover : public GeneticOperation
{
public:
    Crossover();
private:
    CarPtr reproduce(const Parents &parents);
    CarPtr reproduce(const Car *parent);
};

#endif // CROSSOVER_H
