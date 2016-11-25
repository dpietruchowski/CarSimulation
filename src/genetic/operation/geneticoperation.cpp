#include "geneticoperation.h"

CarPtr GeneticOperation::operator()(const GeneticOperation::Parents &parents)
{
    return reproduce(parents);
}
