#include "geneticalgorithm.h"
#include "selection/selection_h.h"
#include <iostream>

using namespace std;

GeneticAlgorithm::GeneticAlgorithm(const GeneticParameters& params):
    size_(params.populationSize), selectionType_(params.selectionType),
    tournamentSize_(params.populationSize/3)
{
    crossoverGenerator_.registerObject(params.probabilities.crossover.onePoint,
                                       OnePointCrossover::create);
    crossoverGenerator_.registerObject(params.probabilities.crossover.twoPoint,
                                       TwoPointCrossover::create);
    crossoverGenerator_.registerObject(params.probabilities.crossover.wheel,
                                       WheelCrossover::create);

    mutationGenerator_.registerObject(params.probabilities.mutation.wheel,
                                      WheelMutation::create);
    mutationGenerator_.registerObject(params.probabilities.mutation.body,
                                      BodyMutation::create);
}

void GeneticAlgorithm::insert(Car* individual)
{
    auto added = population_.insert(make_pair(individual->score(),
                                    CarSPtr(new Car(*individual, false))));
    if(!added.second) {
        return;
    }
//    added.first->second->initialize();
    emit addObject(added.first->second);

    if(population_.size() == size_+1) {
        emit removeObject(population_.rbegin()->second);
        auto removed = population_.erase(population_.rbegin()->first);
        if(removed != 1)
            throw "Not removed or removed more objects";
    }
    //else stats.push_back(0);
}

CarPtr GeneticAlgorithm::create()
{
    std::vector<Car *> parents;
    double chosen = select();
    //stats[chosen]++;
    if (population_.find(chosen) == population_.end())
        throw "Individual not found";
    parents.push_back(population_[chosen].get());
    chosen = select();
    //stats[chosen]++;
    if (population_.find(chosen) == population_.end())
        throw "Individual not found";
    parents.push_back(population_[chosen].get());

    GeneticOperation *crossover = crossoverGenerator_.createRandomPtr();
    GeneticOperation *mutation = mutationGenerator_.createRandomPtr();
    CarPtr parent = (*crossover)(parents);
    parents.clear();
    parents.push_back(parent.get());
    CarPtr child = (*mutation)(parents);
    delete crossover;
    delete mutation;

    return std::move(child);
}

bool GeneticAlgorithm::full() const
{
    return population_.size() >= size_;
}

bool GeneticAlgorithm::empty() const
{
    return population_.empty();
}

double GeneticAlgorithm::select()
{
    Selection *selection = nullptr;
    switch(selectionType_)
    {
    case FITNESS_ROULETTESELECTION:
        selection = new FitnessRouletteSelection();
        break;
    case RANK_ROULETTESELECTION:
        selection = new RankRouletteSelection();
        break;
    case TOURNAMENTSELECTION:
        selection = new TournamentSelection(tournamentSize_);
        break;
    default:
        throw "Bad type";
    }

    int i = 0;
    for(const auto& ind: population_)
    {
        selection->add(i, ind.second->score());
        ++i;
    }
    selection->calcScores();
    double score = selection->selectScore();

    delete selection;
    return score;
}
