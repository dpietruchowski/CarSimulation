#include "mutation.h"
#include "utilfunctions.h"

CarPtr Mutation::reproduce(const GeneticOperation::Parents &parents) const
{
    if(parents.size() != 1)
        throw "Missing parent";

    return reproduce(parents[0]);
}
