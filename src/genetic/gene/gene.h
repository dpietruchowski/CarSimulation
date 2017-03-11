#ifndef GENE_H
#define GENE_H

#include "simulation/element/element.h"

class Gene
{
public:
    Gene(const Element::Parameters &parameters);
    Gene(const Gene &other) = default;
    virtual ~Gene() = default;
    Gene& operator=(const Gene &rhs) = default;

    const Element::Parameters &getParameters() const;
    std::string toString() const;
private:
    virtual void geneToString(std::string &gene) const = 0;
private:
    Element::Parameters parameters_;
};

#endif // GENE_H
