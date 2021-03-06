#include "selectiontypes.h"

Score::Score(unsigned int rank, double score, double value, double normalized):
rank(rank), score(score), value(value), normalized(normalized)
{
}

std::string Score::toString() const
{
    std::string sScore = std::to_string(rank);
    sScore += " ";
    sScore += to_string_with_precision(score, 3);
    sScore += " ";
    sScore += to_string_with_precision(value, 3);
    sScore += " ";
    sScore += to_string_with_precision(normalized, 3);

    return sScore;
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

SelectionRandomGenerator::SelectionRandomGenerator() :
    _re{_rd()}, _dist{0, 100}
{
}

double SelectionRandomGenerator::operator()()
{
     return _dist(_re);
}
