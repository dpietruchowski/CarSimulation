#ifndef WHEELGENE_H
#define WHEELGENE_H

#include "gene.h"
#include "simulation/object/object.h"

///
/// \brief The WheelGene class. Represents gene, which wheel based on.
///
class WheelGene: public Gene
{
public:
    ///
    /// \brief MAX_RADIUS Maximum value of wheel radius.
    ///
    static const int MAX_RADIUS = 3;

public:
    ///
    /// \brief A WheelGene constructor. Creates gene with radius, vertex number
    /// and parameters such as density, friction, restitution.
    /// \param radius Value of wheel radius
    /// \param vertexNumber Vertex number in car body, with whom wheel creates
    /// joint
    /// \param parameters Gene parameters such as density, friction, restitution
    ///
    WheelGene(float32 radius, size_t vertexNumber,
              const Element::Parameters& parameters);

    ///
    /// \brief A WheelGene copy constructor. Creates copy of @
    /// If copied vertex number is greater than maxVertexNumber
    /// than maxVertexNumber is set.
    /// \param other Copied gene
    /// \param maxVertexNumber Maximum value for vertex number
    ///
    WheelGene(const WheelGene &other, size_t maxVertexNumber);
    WheelGene(const WheelGene &other) = default;
    WheelGene &operator=(const WheelGene &rhs) = default;

    ///
    /// \brief operator ==. Compare gene's vertex number.
    /// \param other Gene to compare
    /// \return true if equals, otherwise false
    ///
    bool operator==(const WheelGene &other) const;
    ///
    /// \brief operator !=. Compare gene's vertex number.
    /// \param other Gene to compare
    /// \return true if not equals, otherwise false
    ///
    bool operator!=(const WheelGene &other) const;

    ///
    /// \brief create Creates wheel element, which is used to simulation.
    /// \param position Gene position
    /// \param color Gene colour
    /// \return Created wheel element
    ///
    ElementPtr create(const b2Vec2& position,
                      const Qt::GlobalColor& color) const;

    ///
    /// \brief getVertexNumber Returns vertex number in car body, with whom
    /// wheel creates joint.
    /// \return vertex number in car body, with whom wheel creates joint
    ///
    size_t getVertexNumber() const;

private:
    void geneToString(std::string &gene) const override;

private:
    float32 radius_;
    /// Vertex number in car body, with whom wheel creates joint
    size_t vertexNumber_;

};

#endif // WHEELGENE_H
