#include "onepointcrossover.h"

GeneticOperation *OnePointCrossover::create()
{
    return new OnePointCrossover();
}

OnePointCrossover::OnePointCrossover()
{

}

void OnePointCrossover::addAngles(std::vector<float32> &angles) const
{
    float32 angle = 90 + std::rand() % 180;
    angles.push_back(angle);
    angles.push_back(360);
}
