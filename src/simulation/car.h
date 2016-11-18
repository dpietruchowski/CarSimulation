#ifndef CAR_H
#define CAR_H

#include "object.h"
#include "element/element.h"
#include "genetic/bodygene.h"
#include "genetic/wheelgene.h"

#include <vector>

class Car: public Object
{
public:
    Car(b2Vec2 position);
    void run(float32 torque);

private:
    void initialize(std::vector<ElementPtr>& elements);
    void createJoints(std::vector<ElementPtr>& elements,
                      b2World& world);
    float32 rand(float32 min, float32 max);
private:
    b2Vec2 startPosition_;
    float32 initLength_;
    Qt::GlobalColor color_;
    std::vector<BodyGene> body_;
    std::vector<WheelGene> wheels_;
};

#endif // CAR_H
