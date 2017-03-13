#ifndef MEPSELECTION_H
#define MEPSELECTION_H

#include <random>
#include "selectiontypes.h"

///
/// \brief The Selection class which is responsible for selection in genetic
/// algorithm.
///
class Selection
{
public:
    ///
    /// \brief A Selection constructor. Creates object with specific score type.
    /// \param scoreType Specific score type
    ///
    Selection(ScoreType* scoreType);

    ///
    /// \brief A Selection destructor. Deletes score type pointer.
    ///
    virtual ~Selection();

    ///
    /// \brief Adds individual to selection with rank and score.
    /// \param rank Individual's rank in population
    /// \param score Individual's fitness score
    ///
    void add(unsigned int rank, double score);

    ///
    /// \brief Calculates probability for all individuals added to selection.
    ///
    void calcScores();

    ///
    /// \brief Returns all scores added to selection.
    /// \return Scores added to selection
    ///
    Scores getScores() const;

    ///
    /// \brief Selects individual and returns its rank.
    /// \return Selected individual's rank
    ///
    unsigned int selectRank() const;

    ///
    /// \brief Selects individual and returns its fitness score.
    /// \return Selected individual's fitness score.
    ///
    double selectScore() const;
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
