#ifndef TWOPOINTCROSSOVER_H
#define TWOPOINTCROSSOVER_H

#include "crossover.h"

///
/// \brief The TwoPointCrossover class.
///
class TwoPointCrossover : public Crossover
{
public:
    ///
    /// \brief Creates new TwoPointCrossover object.
    /// \return Newly created object
    ///
    static GeneticOperation *create();
    TwoPointCrossover();
private:
    void addAngles(std::vector<float32> &angles) const;
};

#endif // TWOPOINTCROSSOVER_H
