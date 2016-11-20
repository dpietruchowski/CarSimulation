#ifndef MEPSELECTION_H
#define MEPSELECTION_H

#include <random>
#include "selectiontypes.h"

class Selection
{
public:
    Selection(ScoreType*);
    virtual ~Selection();

    void add(unsigned int rank, double score);
    void calcScores();
    Scores getScores() { return scores_; }
    unsigned int select() const;
protected:
//    SelectionRandomGenerator generator_;

private:
    virtual int select(const Scores&) const = 0;
    virtual void calcScores(Scores&, double worstScore) = 0;
private:
    Scores scores_;
    ScoreType* scoreType_;
    double worstScore_;
};

#endif
