#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <map>
#include "simulation/car.h"
#include "selection/selection.h"

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(unsigned int populationSize, SelectionType selectionType);
    
    void insert(CarPtr individual);
    CarPtr create();

private:
    unsigned int select();
    
private:
    typedef std::vector<CarPtr> Population_;
    Population_ population_;
    unsigned int populationSize_;
    SelectionType selectionType_;
    unsigned int tournamentSize_;
    std::vector<int> stats;
};

#endif // GENETICALGORITHM_H
