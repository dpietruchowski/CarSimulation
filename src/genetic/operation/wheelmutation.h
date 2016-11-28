#ifndef WHEELMUTATION_H
#define WHEELMUTATION_H

#include "mutation.h"

class WheelMutation : public Mutation
{
public:
    static GeneticOperation *create();
    WheelMutation();
private:
    CarPtr reproduce(const Car *parent) const;
};

#endif // WHEELMUTATION_H
