#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <map>
#include "simulation/car.h"

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(unsigned int populationSize);
    
    void insert(float score, CarPtr individual);
    CarPtr create();
    
private:
    typedef std::multimap<float, CarPtr> Population_;
    Population_ population_;
    int populationSize_;
};

#endif // GENETICALGORITHM_H
