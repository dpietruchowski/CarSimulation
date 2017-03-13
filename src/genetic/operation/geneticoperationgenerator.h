#ifndef GENETICOPERATIONGENERATOR_H
#define GENETICOPERATIONGENERATOR_H

#include "generator.h"

class GeneticOperation;

///
/// \brief The GeneticOperationGenerator class, which is responsible for random
/// genetic operation generation
///
class GeneticOperationGenerator
{
public:
    ///
    /// Callback, which creates genetic operation object
    ///
    typedef GeneticOperation* (*CreateObjectFunction)();
    GeneticOperationGenerator() = default;

public:
    ///
    /// \brief Creates pointer to random generated genetic operation object
    /// \return
    ///
    GeneticOperation* createRandomPtr();

    ///
    /// \brief Registers callback, which creates genetic operation object with
    /// probability
    /// \param probability Probability of this callback
    /// \param function Callback, which creates gneetic operation object
    ///
    void registerObject(double probability, CreateObjectFunction function);

private:
    Generator<CreateObjectFunction> generator_;
};

#endif // GENETICOPERATIONGENERATOR_H
