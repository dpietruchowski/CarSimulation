#ifndef ONEPOINTCROSSOVER_H
#define ONEPOINTCROSSOVER_H

#include "crossover.h"

///
/// \brief The OnePointCrossover class.
///
class OnePointCrossover : public Crossover
{
public:
    ///
    /// \brief Creates new OnePointCrossover object.
    /// \return Newly created object
    ///
    static GeneticOperation *create();
    OnePointCrossover();
private:
    void addAngles(std::vector<float32> &angles) const;
};

#endif // ONEPOINTCROSSOVER_H
