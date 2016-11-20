#ifndef CAR_H
#define CAR_H

#include "object.h"
#include "element/element.h"
#include "genetic/gene/bodygene.h"
#include "genetic/gene/wheelgene.h"

#include <vector>

class Car;
typedef std::unique_ptr<Car> CarPtr;

class Car: public Object
{

public:
    Car(b2Vec2 position);
    inline bool operator==(const Car& rhs)
        { return score_ == rhs.score_; }
    inline bool operator!=(const Car& rhs)
        { return !operator==(rhs); }
    inline bool operator< (const Car& rhs)
        { return score_ < rhs.score_; }
    inline bool operator> (const Car& rhs)
        { return score_ > rhs.score_; }
    inline bool operator<=(const Car& rhs)
        { return score_ <= rhs.score_; }
    inline bool operator>=(const Car& rhs)
        { return score_ >= rhs.score_; }
    void run(float32 torque);
    double getScore() { return score_; }
    void setScore(double score) { score_ = score; }

private:
    void initialize(std::vector<ElementPtr>& elements);
    void createJoints(std::vector<ElementPtr>& elements,
                      b2World& world);
    float32 rand(float32 min, float32 max);
private:
    double score_;
    b2Vec2 startPosition_;
    float32 initLength_;
    Qt::GlobalColor color_;
    std::vector<BodyGene> body_;
    std::vector<WheelGene> wheels_;
};

#endif // CAR_H
