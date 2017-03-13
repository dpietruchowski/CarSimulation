#ifndef BODYMUTATION_H
#define BODYMUTATION_H

#include "mutation.h"

///
/// \brief The BodyMutation class, which represents mutation of body.
///
class BodyMutation : public Mutation
{
public:
    ///
    /// \brief Creates new BodyMutation object.
    /// \return Newly created object
    ///
    static GeneticOperation *create();
    BodyMutation() = default;
private:
    CarPtr reproduce(const Car *parent) const override;
};

#endif // BODYMUTATION_H
