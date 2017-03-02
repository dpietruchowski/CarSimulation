#include "selectiontypes.h"

Score::Score(unsigned int rank, double score, double value, double normalized):
rank(rank), score(score), value(value), normalized(normalized)
{
}

Score FitnessScore::add(unsigned int rank, double fitness) const
{
    return Score{rank, fitness, fitness, 0};
}

double FitnessScore::changeWorstScore(double /* unused */) const
{
    return 0;
}

Score RankScore::add(unsigned int rank, double fitness) const
{
    return Score{rank, fitness, static_cast<double>(rank), 0};
}

double RankScore::changeWorstScore(double worstScore) const
{
    return worstScore;
}
