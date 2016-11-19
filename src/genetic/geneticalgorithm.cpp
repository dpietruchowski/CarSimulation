#include "geneticalgorithm.h"

using namespace std;

GeneticAlgorithm::GeneticAlgorithm(unsigned int populationSize):
    populationSize_(populationSize)
{
    
}

void GeneticAlgorithm::insert(float score, CarPtr individual)
{
    if(population_.size() == populationSize_)
        population_.erase(population_.begin());
    population_.insert(make_pair(score, move(individual)));
}

CarPtr GeneticAlgorithm::create()
{
    // Will be implemented after selection and genetic operation creation

    return nullptr;
}
