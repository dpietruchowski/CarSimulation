#ifndef GENETICOPERATIONGENERATOR_H
#define GENETICOPERATIONGENERATOR_H

#include "generator.h"

class GeneticOperation;

class GeneticOperationGenerator
{
public:
    typedef GeneticOperation* (*CreateObjectFunction)();
    GeneticOperationGenerator();
public:
    GeneticOperation* createRandomPtr();
    void registerObject(double probability, CreateObjectFunction function);

private:
    Generator<CreateObjectFunction> generator_;
};

#endif // GENETICOPERATIONGENERATOR_H
