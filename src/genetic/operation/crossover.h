#ifndef CROSSOVER_H
#define CROSSOVER_H

#include "geneticoperation.h"

///
/// \brief The Crossover class, which represents crossover operation
///
class Crossover : public GeneticOperation
{
public:
    Crossover() = default;
private:
    CarPtr reproduce(const Parents &parents) const;
    virtual void addAngles(std::vector<float32> &angles) const {}
    virtual CarPtr reproduce(const Car *parent1,
                             const Car *parent2) const;
};

#endif // CROSSOVER_H
