#include "rouletteselection.h"
#include "selectiontypes.h"

static SelectionRandomGenerator generator;

#include <cstdlib>

RouletteSelection::RouletteSelection(ScoreType* scoreType):
    Selection(scoreType)
{
}


//TODO use library to choose by probabilities
int RouletteSelection::select(const Scores& scores) const
{
    double decision = const_cast<SelectionRandomGenerator&> (generator)();
    double sum = 0;
    int i = 0;
    double sumofScores = 0;
    for(const auto& score: scores)
    {
        sumofScores += score.normalized;
    }
    for(const auto& score: scores)
    {
        sum += score.normalized;
        if(decision <= sum)
            return i;
        i++;
    }
    //should never get here
    assert(0);
    return i;
}

void RouletteSelection::calcScores(Scores& scores, double worstScore)
{
    double sumOfScores = 0;
    for(auto& score : scores)
    {
        score.value = abs(worstScore - score.value + 1);
        sumOfScores += score.value;
    }

    for(auto& score : scores)
        score.normalized = (score.value * 100) / sumOfScores;
}

RankRouletteSelection::RankRouletteSelection():
    RouletteSelection(new RankScore())
{
}

FitnessRouletteSelection::FitnessRouletteSelection():
    RouletteSelection(new FitnessScore())
{
}
