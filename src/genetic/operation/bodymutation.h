#ifndef BODYMUTATION_H
#define BODYMUTATION_H

#include "mutation.h"

class BodyMutation : public Mutation
{
public:
    static GeneticOperation *create();
    BodyMutation();
private:
    CarPtr reproduce(const Car *parent) const;
};

#endif // BODYMUTATION_H
