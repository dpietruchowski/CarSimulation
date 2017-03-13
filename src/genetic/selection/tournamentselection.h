#ifndef TOURNAMENTSELECTION_H
#define TOURNAMENTSELECTION_H

#include "selection.h"

///
/// \brief The TournamentSelection class that represents tournament selection.
/// Individaul's probability is calculated by this formula:
/// probability = score / worstScore.
/// First part of individuals are random selected to tournament. After that
/// one of them is selected by calculated probability.
///
class TournamentSelection: public Selection
{
public:
    ///
    /// \brief A TournamentSelection constructor.
    /// \param tournamentSize The size of tournament
    ///
    TournamentSelection(int tournamentSize);

private:
    int select(const Scores&) const override;
    void calcScores(Scores&, double worstScore) override;
private:
    int tournamentSize_;
};

#endif
