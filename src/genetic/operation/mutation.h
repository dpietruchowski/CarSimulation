#ifndef MUTATION_H
#define MUTATION_H

#include "geneticoperation.h"

///
/// \brief The Mutation class, which represents mutation operation
///
class Mutation : public GeneticOperation
{
public:
    Mutation() = default;
private:
    CarPtr reproduce(const Parents &parents) const;
    virtual CarPtr reproduce(const Car *parent) const = 0;
};

#endif // MUTATION_H
