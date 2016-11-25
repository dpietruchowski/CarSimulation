#ifndef GENETICOPERATION_H
#define GENETICOPERATION_H

#include "simulation/car.h"

class GeneticOperation
{
public:
    typedef std::vector<Car*> Parents;
    GeneticOperation() = default;

    CarPtr operator()(const Parents& parents);

private:
    virtual CarPtr reproduce(const Parents &parents) = 0;
};

#endif // GENETICOPERATION_H
