#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <map>
#include <QObject>
#include "simulation/object/car.h"
#include "selection/selection.h"
#include "operation/operation.h"

//TODO add probability params
struct GeneticParameters
{
    size_t populationSize;
    SelectionType selectionType;
};

class GeneticAlgorithm: public QObject
{
    Q_OBJECT
public:
    GeneticAlgorithm(GeneticParameters params);
    
    void insert(Car* individual);
    CarPtr create();
    bool full() const;
    bool empty() const;

signals:
    void addObject(CarSPtr);
    void removeObject(CarSPtr);

private:
    double select();
    
private:
    typedef std::map<double, CarSPtr, std::greater<double>> Population_;
    Population_ population_;
    GeneticOperationGenerator crossoverGenerator_;
    GeneticOperationGenerator mutationGenerator_;
    size_t size_;
    SelectionType selectionType_;
    unsigned int tournamentSize_;
    //std::vector<int> stats;
};

#endif // GENETICALGORITHM_H
