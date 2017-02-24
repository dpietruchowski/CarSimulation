#include "geneticalgorithm.h"
#include "selection/selection_h.h"
#include <iostream>

using namespace std;

GeneticAlgorithm::GeneticAlgorithm(GeneticParameters params):
    size_(params.populationSize), selectionType_(params.selectionType),
    tournamentSize_(params.populationSize/3)
{
    crossoverGenerator_.registerObject(0.5, OnePointCrossover::create);
    crossoverGenerator_.registerObject(0.3, TwoPointCrossover::create);
    crossoverGenerator_.registerObject(0.2, WheelCrossover::create);

    mutationGenerator_.registerObject(0.5, WheelMutation::create);
    mutationGenerator_.registerObject(0.5, BodyMutation::create);
}

void GeneticAlgorithm::insert(Car* individual)
{
    for(const auto &c: population_)
    {
        if(*individual == *c)
            return;
    }

    if(population_.size() == size_)
        population_.erase(population_.end());
    else stats.push_back(0);
    population_.push_back(CarPtr(new Car(*individual, false)));
    std::sort(population_.begin(), population_.end(),
              [](const CarPtr &lhs, const CarPtr &rhs)
                { return *lhs > *rhs; });
}

CarPtr GeneticAlgorithm::create()
{
    std::vector<Car *> parents;
    int chosen = select();
    stats[chosen]++;
    parents.push_back(population_[chosen].get());
    chosen = select();
    stats[chosen]++;
    parents.push_back(population_[chosen].get());

    GeneticOperation *crossover = crossoverGenerator_.createRandomPtr();
    GeneticOperation *mutation = mutationGenerator_.createRandomPtr();
    CarPtr parent = (*crossover)(parents);
    parents.clear();
    parents.push_back(parent.get());
    CarPtr child = (*mutation)(parents);
    delete crossover;
    delete mutation;

    /*cout << "////////" << endl;
    int i = 0;
    for (const auto & s: stats) {
        cout << "[" << population_[i]->score() << "]" << "[" << i << "]: " << s << endl;
        ++i;
    }*/

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

unsigned int GeneticAlgorithm::select()
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
        selection->add(i, ind->score());
        ++i;
    }
    selection->calcScores();
    unsigned int rank = selection->select();

    delete selection;
    return rank;
}
