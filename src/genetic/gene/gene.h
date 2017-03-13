#ifndef GENE_H
#define GENE_H

#include "simulation/element/element.h"

///
/// \brief The Gene class. Gene class is a primary element of genetic module.
/// Object's elements are created based on this class.
///
class Gene
{
public:
    ///
    /// \brief A Gene constructor. Creates gene with parameters.
    /// \param parameters Gene parameters such as density, friction, restitution
    ///
    Gene(const Element::Parameters &parameters);
    Gene(const Gene &other) = default;
    virtual ~Gene() = default;
    Gene& operator=(const Gene &rhs) = default;

    ///
    /// \brief getParameters Returns gene parameters such as density, friction,
    /// restitution.
    /// \return gene parameters
    ///
    const Element::Parameters &getParameters() const;

    ///
    /// \brief toString Return gene string representation.
    /// \return gene string representation
    ///
    std::string toString() const;
private:
    virtual void geneToString(std::string &gene) const = 0;
private:
    Element::Parameters parameters_;
};

#endif // GENE_H
