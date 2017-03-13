#ifndef BODYGENE_H
#define BODYGENE_H

#include "gene.h"

///
/// \brief The BodyGene class that contains information about body's part
/// as angle, length, parameters (friction, density, restitution), and vertice,
/// which is shared with other part of body. One vertex is center of car body
/// and common for all parts.
///
class BodyGene: public Gene
{
public:
    ///
    /// \brief MAX_LENGTH Maximum value of body's part length.
    ///
    static const int MAX_LENGTH = 8;
    ///
    /// \brief MIN_LENGTH Minimum value of body's part length.
    ///
    static const int MIN_LENGTH = 2;

public:
    ///
    /// \brief A BodyGene constructor. Creates gene with parameters such as
    /// density, friction, restitution and with vertex of body's part
    /// \param parameters Gene parameters such as density, friction, restitution
    /// \param vertex The vertex of body's part
    ///
    BodyGene(const Element::Parameters &parameters, const b2Vec2 &vertex);
    BodyGene(const BodyGene &other) = default;
    ~BodyGene() = default;
    BodyGene &operator=(const BodyGene &rhs) = default;

    /// Create polygon shape as triangle with vertices:
    /// First vertex is center of car's body and this is position of car
    /// Second vertex is shared with previous part of body
    /// Third vertex is calculated and shared with next part of body

    ///
    /// \brief Creates polygon shape as triangle with vertices:
    /// First vertex is center of car's body and this is position of car
    /// Second vertex is shared with previous part of body
    /// Third vertex is calculated and shared with next part of body
    /// \param vertex Vertex that is shared with previous part of body
    /// \return Polygon shape
    ///
    b2Shape* create(const b2Vec2& vertex);

    ///
    /// \brief getVertex Returns vertex of body's part.
    /// \return Vertex of body's part
    ///
    const b2Vec2 &getVertex() const;

private:
    void geneToString(std::string &gene) const override;

private:
    b2Vec2 vertex_;
};

#endif // BODYGENE_H
