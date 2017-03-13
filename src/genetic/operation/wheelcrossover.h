#ifndef WHEELCROSSOVER_H
#define WHEELCROSSOVER_H

#include "crossover.h"

///
/// \brief The WheelCrossover class.
///
class WheelCrossover : public Crossover
{
public:
    ///
    /// \brief Creates new WheelCrossover object.
    /// \return Newly created object
    ///
    static GeneticOperation *create();
    WheelCrossover() = default;
private:
    CarPtr reproduce(const Car *parent1,
                     const Car *parent2) const;
};

#endif // WHEELCROSSOVER_H
