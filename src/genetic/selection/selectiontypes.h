#ifndef SELECTIONTYPES_H
#define SELECTIONTYPES_H

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <random>
#include <Box2D/Common/b2Settings.h>

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out << std::setprecision(n) << a_value;
    return out.str();
}


class SelectionRandomGenerator
{
public:
    explicit SelectionRandomGenerator() : _re{_rd()}, _dist{0, 100} {}
    double operator()() { return _dist(_re); }
private:
    std::random_device _rd;
    std::mt19937 _re;
    std::uniform_real_distribution<double> _dist;
};

enum SelectionType
{
    FITNESS_ROULETTESELECTION,
    RANK_ROULETTESELECTION,
    TOURNAMENTSELECTION
};

inline SelectionType selectionTypeFromString(std::string& enm)
{
    if(enm == "FITNESS_ROULETTESELECTION") return FITNESS_ROULETTESELECTION;
    if(enm == "RANK_ROULETTESELECTION") return RANK_ROULETTESELECTION;
    if(enm == "TOURNAMENTSELECTION") return TOURNAMENTSELECTION;

    throw std::string("Wrong enum");
}

inline std::string selectionTypeToString(SelectionType type)
{
    if(type == FITNESS_ROULETTESELECTION) return "FITNESS_ROULETTESELECTION";
    if(type == RANK_ROULETTESELECTION) return "RANK_ROULETTESELECTION";
    if(type == TOURNAMENTSELECTION) return "TOURNAMENTSELECTION";

    throw std::string("Wrong enum");
}

struct Score
{
    unsigned int rank;
    double score;
    double value;
    double normalized;
    Score(const Score&) = default;
    Score(unsigned int, double, double, double);
    std::string toString() const
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
};
typedef std::vector<Score> Scores;

struct ScoreType
{
    virtual ~ScoreType() = default;
    virtual Score add(unsigned int rank, double fitness) const = 0;
    virtual double changeWorstScore(double worstScore) const = 0;
};

struct FitnessScore: public ScoreType
{
    Score add(unsigned int rank, double fitness) const;
    double changeWorstScore(double worstScore) const;
};

struct RankScore: public ScoreType
{
    Score add(unsigned int rank, double fitness) const;
    double changeWorstScore(double worstScore) const;
};

#endif
