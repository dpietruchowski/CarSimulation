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

///
/// \brief The SelectionRandomGenerator class that generates random double
/// number from 0 to 100 with uniform distribution.
///
class SelectionRandomGenerator
{
public:
    ///
    /// \brief A SelectionRandomGenerator constructor.
    ///
    explicit SelectionRandomGenerator();
    ///
    /// \brief operator (). Generates random double number
    /// from 0 to 100 with uniform distribution.
    /// \return Random number from 0 to 100
    ///
    double operator()();
private:
    std::random_device _rd;
    std::mt19937 _re;
    std::uniform_real_distribution<double> _dist;
};

///
/// \brief The SelectionType enum for selection type
///
enum SelectionType
{
    FITNESS_ROULETTESELECTION, ///< fitness roulette selection
    RANK_ROULETTESELECTION,    ///< rank roulette selection
    TOURNAMENTSELECTION        ///< tournament selection
};

///
/// \brief Funtion which maps selection type from string.
/// \param enm Selection type as string
/// \return Selection type
///
inline SelectionType selectionTypeFromString(std::string& enm)
{
    if(enm == "FITNESS_ROULETTESELECTION") return FITNESS_ROULETTESELECTION;
    if(enm == "RANK_ROULETTESELECTION") return RANK_ROULETTESELECTION;
    if(enm == "TOURNAMENTSELECTION") return TOURNAMENTSELECTION;

    throw std::string("Wrong enum");
}

///
/// \brief Function which maps selection type to string
/// \param type Selection type
/// \return Selection type as string
///
inline std::string selectionTypeToString(SelectionType type)
{
    if(type == FITNESS_ROULETTESELECTION) return "FITNESS_ROULETTESELECTION";
    if(type == RANK_ROULETTESELECTION) return "RANK_ROULETTESELECTION";
    if(type == TOURNAMENTSELECTION) return "TOURNAMENTSELECTION";

    throw std::string("Wrong enum");
}

///
/// \brief The Score struct that represents individual's score needed to
/// evaluate their usefulness in population and calculate probability of
/// the selection
///
struct Score
{
    unsigned int rank; ///< Rank tells how individual is good in population.
                       ///< This is relative parameter.
    double score;      ///< This fitness score is absolute parameter.
    double value;      ///< Value depends on the type of score.
                       ///< This can be equal to rank or to score
    double normalized; ///< Normalized is probability of the selection
                       ///< calculated by value
    Score(const Score&) = default;

    ///
    /// \brief A Score constructor.
    ///
    Score(unsigned int, double, double, double);

    ///
    /// \brief Converts object to its string representation.
    /// \return String representation of the object
    ///
    std::string toString() const;
};

///
/// \brief Vector of the scores.
///
typedef std::vector<Score> Scores;

///
/// \brief The ScoreType struct that represents score type
///
struct ScoreType
{
    virtual ~ScoreType() = default;

    ///
    /// \brief Creates score based on score type
    /// \param rank Rank of the individual in population
    /// \param fitness Individual's fitness score
    /// \return Created score
    ///
    virtual Score add(unsigned int rank, double fitness) const = 0;

    ///
    /// \brief Returns worst score
    /// \param worstScore The worst score
    /// \return The worst score
    ///
    virtual double changeWorstScore(double worstScore) const = 0;
};

///
/// \brief The FitnessScore struct that represents fitness score type
///
struct FitnessScore: public ScoreType
{
    ///
    /// \brief Creates score with value equals to fitness. Probability is
    /// calculated based on value.
    /// \param rank Rank of the individual in population
    /// \param fitness Individual's fitness score
    /// \return Created score
    ///
    Score add(unsigned int rank, double fitness) const override;

    ///
    /// \brief Returns worst score which is equal to argument for this type
    /// \param worstScore The worst score
    /// \return The worst score
    ///
    double changeWorstScore(double worstScore) const override;
};

///
/// \brief The RankScore struct that represents rank score type
///
struct RankScore: public ScoreType
{
    ///
    /// \brief Creates score with value equals to rank. Probability is
    /// calculated based on value.
    /// \param rank Rank of the individual in population
    /// \param fitness Individual's fitness score
    /// \return Created score
    ///
    Score add(unsigned int rank, double fitness) const override;

    ///
    /// \brief Returns worst score, which is 0 for this type
    /// \param worstScore The worst score (not used here)
    /// \return 0
    ///
    double changeWorstScore(double worstScore) const override;
};

#endif
