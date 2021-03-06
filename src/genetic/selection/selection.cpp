#include "selection.h"
#include <algorithm>

Selection::Selection(ScoreType* scoreType)
//    generator_()
{
    scoreType_ = scoreType;
    worstScore_ = 0;
}

Selection::~Selection()
{
    delete scoreType_;
}

void Selection::add(unsigned int rank, double fitness)
{
    Score score = scoreType_->add(rank, fitness);
    if(score.value > worstScore_)
        worstScore_ = score.value;

    scores_.push_back(score);
}

void Selection::calcScores()
{
    std::random_shuffle(scores_.begin(), scores_.end());
    worstScore_ = scoreType_->changeWorstScore(worstScore_);
    calcScores(scores_, worstScore_);
}

Scores Selection::getScores() const
{
    return scores_;
}

double Selection::selectScore() const
{
    int selected = select(scores_);
    assert(selected < scores_.size());
    return scores_[selected].score;
}

unsigned int Selection::selectRank() const
{
    int selected = select(scores_);
    assert(selected < scores_.size());
    return scores_[selected].rank;
}
