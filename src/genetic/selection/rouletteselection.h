#ifndef ROULETTESELECTION_H
#define ROULETTESELECTION_H

#include "selection.h"

///
/// \brief The RouletteSelection class that represents roulette selection.
///
class RouletteSelection: public Selection
{
public:
    ///
    /// \brief A RouletteSelection constructor. Creates object with specific
    /// score type.
    /// \param scoreType Specific score type
    ///
    RouletteSelection(ScoreType* scoreType);

private:
    int select(const Scores&) const override;
    void calcScores(Scores&, double worstScore) override;
};

///
/// \brief The RankRouletteSelection class that represents rank roulette
/// selection.
///
class RankRouletteSelection: public RouletteSelection
{
public:
    ///
    /// \brief A RankRouletteSelection constructor. Creates object with rank
    /// score type.
    ///
    RankRouletteSelection();
};

///
/// \brief The FitnessRouletteSelection class that represents fitness roulette
/// selection.
///
class FitnessRouletteSelection: public RouletteSelection
{
public:
    ///
    /// \brief A FitnessRouletteSelection constructor. Creates object with
    /// fitness score type.
    ///
    FitnessRouletteSelection();
};

#endif
