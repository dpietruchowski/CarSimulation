#ifndef ONEPOINTCROSSOVER_H
#define ONEPOINTCROSSOVER_H

#include "crossover.h"

class OnePointCrossover : public Crossover
{
public:
    static GeneticOperation *create();
    OnePointCrossover();
private:
    void addAngles(std::vector<float32> &angles) const;
};

#endif // ONEPOINTCROSSOVER_H
