#include "wheelcrossover.h"

GeneticOperation *WheelCrossover::create()
{
    return new WheelCrossover();
}

WheelCrossover::WheelCrossover()
{

}

CarPtr WheelCrossover::reproduce(const Car *parent1, const Car *parent2) const
{
    return CarPtr(new Car(*parent1, *parent2));
}
