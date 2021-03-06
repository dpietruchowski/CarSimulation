#include "geneticoperationgenerator.h"

GeneticOperation *GeneticOperationGenerator::createRandomPtr()
{
    CreationCounter<CreateObjectFunction> counter = generator_.createRandom();
    CreateObjectFunction function = counter.callbackFunction;

    return function();
}

void GeneticOperationGenerator::registerObject(double probability,
                       GeneticOperationGenerator::CreateObjectFunction function)
{
    generator_.registerCallback(probability, function);
}
