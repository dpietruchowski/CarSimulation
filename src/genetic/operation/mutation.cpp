#include "mutation.h"
#include "utilfunctions.h"

CarPtr Mutation::reproduce(const GeneticOperation::Parents &parents)
{
    if(parents.size() != 1)
        throw "Missing parent";

    return reproduce(parents[0]);
}

CarPtr Mutation::reproduce(const Car *parent)
{
    b2Vec2 vertex(0,0);
    do
    {
        int minAngle = 10;
        int angle = minAngle + std::rand() % (360 - minAngle);
        int maxLength = (BodyGene::MAX_LENGTH - 1) * 100;
        float32 length = static_cast<float>(1 + std::rand() % maxLength) / maxLength;
        length *= (BodyGene::MAX_LENGTH - 1);
        length += 1;
        vertex = VertexCalculation()(b2Vec2(length, 0), angle, length);
    } while ( !parent->isVertexSettable(vertex) );

    Element::Parameters param = Element::Parameters::createRandom();
    BodyGene gene(param, vertex);

    return CarPtr(new Car(*parent, gene));
}
