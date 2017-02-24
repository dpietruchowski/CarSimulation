#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <map>
#include "simulation/object/car.h"
#include "selection/selection.h"
#include "operation/operation.h"

//TODO add probability params
struct GeneticParameters
{
    size_t populationSize;
    SelectionType selectionType;
};

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(GeneticParameters params);
    
    void insert(Car* individual);
    CarPtr create();
    bool full() const;
    bool empty() const;

private:
    unsigned int select();
    
private:
    typedef std::vector<CarPtr> Population_;
    Population_ population_;
    GeneticOperationGenerator crossoverGenerator_;
    GeneticOperationGenerator mutationGenerator_;
    size_t size_;
    SelectionType selectionType_;
    unsigned int tournamentSize_;
    std::vector<int> stats;
};

#endif // GENETICALGORITHM_H
