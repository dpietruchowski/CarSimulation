#ifndef TOURNAMENTSELECTION_H
#define TOURNAMENTSELECTION_H

#include "selection.h"

class TournamentSelection: public Selection
{
public:
    TournamentSelection(int tournamentSize);

private:
    int select(const Scores&) const;
    void calcScores(Scores&, double worstScore);
private:
    int tournamentSize_;
};

#endif
