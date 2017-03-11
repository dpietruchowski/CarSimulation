#include "gene.h"

Gene::Gene(const Element::Parameters &parameters):
    parameters_(parameters)
{
}

const Element::Parameters &Gene::getParameters() const
{
    return parameters_;
}

std::string Gene::toString() const
{
    std::string sGene;
    geneToString(sGene);
    sGene += parameters_.toString();

    return sGene;
}

