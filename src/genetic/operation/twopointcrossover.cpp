#include "twopointcrossover.h"

GeneticOperation *TwoPointCrossover::create()
{
    return new TwoPointCrossover();
}

TwoPointCrossover::TwoPointCrossover()
{

}

void TwoPointCrossover::addAngles(std::vector<float32> &angles) const
{
    float32 angle = 45 + std::rand() % 90;
    angles.push_back(angle);
    angle = 45 + std::rand() % 90;
    angles.push_back(angle);
    angles.push_back(360);
}
