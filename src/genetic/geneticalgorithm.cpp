#include "geneticalgorithm.h"
#include "selection/selection_h.h"
#include "operation/crossover.h"
#include "operation/mutation.h"
#include <iostream>

using namespace std;

GeneticAlgorithm::GeneticAlgorithm(size_t size,
                                   SelectionType selectionType):
    size_(size), selectionType_(selectionType),
    tournamentSize_(size/3)
{

}

void GeneticAlgorithm::insert(CarPtr individual)
{
    if(population_.size() == size_)
        population_.erase(population_.end());
    else stats.push_back(0);
    population_.push_back(move(individual));
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

    CarPtr parent = Crossover()(parents);
    parents.clear();
    parents.push_back(parent.get());
    CarPtr child = Mutation()(parents);
    cout << "////////" << endl;
    int i = 0;
    for (const auto & s: stats) {
        cout << "[" << population_[i]->score() << "]" << "[" << i << "]: " << s << endl;
        ++i;
    }

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
