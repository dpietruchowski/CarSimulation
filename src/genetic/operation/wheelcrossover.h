#ifndef WHEELCROSSOVER_H
#define WHEELCROSSOVER_H

#include "crossover.h"

class WheelCrossover : public Crossover
{
public:
    static GeneticOperation *create();
    WheelCrossover();
private:
    CarPtr reproduce(const Car *parent1,
                     const Car *parent2) const;
};

#endif // WHEELCROSSOVER_H
