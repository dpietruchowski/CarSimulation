#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <map>
#include <QObject>
#include "simulation/object/car.h"
#include "selection/selection.h"
#include "operation/operation.h"

//TODO add probability params
///
/// \brief The GeneticParameters struct that are used in genetic algorithm
///
struct GeneticParameters
{
    size_t populationSize;       ///< Size of the population
    SelectionType selectionType; ///< Type of the selection
};

///
/// \brief The GeneticAlgorithm class that represent genetic algorithm include
/// selection and genetic operation.
///
class GeneticAlgorithm: public QObject
{
    Q_OBJECT
public:
    ///
    /// \brief A GeneticAlgorithm constructor with genetic parameters.
    /// \param params The genetic parameters
    ///
    GeneticAlgorithm(GeneticParameters params);
    
    ///
    /// \brief Inserts individual to population. If population is full than
    /// the worst individual is removed.
    /// \param individual Individual to be inserted
    ///
    void insert(Car* individual);

    ///
    /// \brief Creates new individuals in genetic way using selection and
    /// genetic operations.
    /// \return Newly created individual
    ///
    CarPtr create();

    ///
    /// \brief Query if population is full.
    /// \return true if population is full, otherwise false
    ///
    bool full() const;

    ///
    /// \brief Query if population is empty.
    /// \return true if population is empty, otherwise false
    ///
    bool empty() const;

signals:
    ///
    /// \brief An addObject signal. This signal is emited when new individual is
    /// added to population.
    /// \param ind Individual, which is added to population
    ///
    void addObject(CarSPtr ind);

    ///
    /// \brief A removeObject signal. This signal is emited when individual is
    /// removed from population.
    /// \param ind Individual, which is removed from population
    ///
    void removeObject(CarSPtr ind);

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
