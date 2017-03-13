#ifndef WHEELMUTATION_H
#define WHEELMUTATION_H

#include "mutation.h"

///
/// \brief The WheelMutation class.
///
class WheelMutation : public Mutation
{
public:
    ///
    /// \brief Creates new WheelMutation object.
    /// \return Newly created object
    ///
    static GeneticOperation *create();
    WheelMutation() = default;
private:
    CarPtr reproduce(const Car *parent) const override;
};

#endif // WHEELMUTATION_H
