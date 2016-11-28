#include "geneticoperation.h"

CarPtr GeneticOperation::operator()(const GeneticOperation::Parents &parents) const
{
    return reproduce(parents);
}
