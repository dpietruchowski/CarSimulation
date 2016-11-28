#ifndef TWOPOINTCROSSOVER_H
#define TWOPOINTCROSSOVER_H

#include "crossover.h"

class TwoPointCrossover : public Crossover
{
public:
    static GeneticOperation *create();
    TwoPointCrossover();
private:
    void addAngles(std::vector<float32> &angles) const;
};

#endif // TWOPOINTCROSSOVER_H
