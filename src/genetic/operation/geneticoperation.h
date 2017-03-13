#ifndef GENETICOPERATION_H
#define GENETICOPERATION_H

#include "simulation/object/car.h"

///
/// \brief The GeneticOperation class, which is based class for crossover and
/// mutation operation
///
class GeneticOperation
{
public:
    ///
    /// \brief Vector of pointers to Car object
    ///
    typedef std::vector<Car*> Parents;
    GeneticOperation() = default;
    virtual ~GeneticOperation() = default;

    ///
    /// \brief operator (). Creates child object from parents
    /// \param parents Parents for genetic operation
    /// \return Child created from parents
    ///
    CarPtr operator()(const Parents& parents) const;

private:
    virtual CarPtr reproduce(const Parents &parents) const = 0;
};

#endif // GENETICOPERATION_H
