#ifndef GENETICOPERATION_H
#define GENETICOPERATION_H

#include "simulation/car.h"

class GeneticOperation
{
public:
    typedef std::vector<Car*> Parents;
    GeneticOperation();

    CarPtr operator()(const Parents& parents);

private:
    CarPtr reproduce(const Parents &parents) = 0;
};

#endif // GENETICOPERATION_H
