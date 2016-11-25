#ifndef MUTATION_H
#define MUTATION_H

#include "geneticoperation.h"

class Mutation : public GeneticOperation
{
public:
    Mutation();
private:
    CarPtr reproduce(const Parents &parents);
    CarPtr reproduce(const Car *parent);
};

#endif // MUTATION_H
