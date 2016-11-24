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
    Car(const Car &other);
    Car(const Car &other, const WheelGene &gene, size_t geneIndex);
    Car(const Car &other, const BodyGene &gene);
    Car(const Car &first, const Car &second,
        const std::vector<float32> &angles);
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
    double getScore() const { return score_; }
    void calcScore();
    std::string toString() const;

private:
    void initialize(std::vector<ElementPtr>& elements);
    void createJoints(std::vector<ElementPtr>& elements,
                      b2World& world);
    void updateObject(double interval);
    float32 rand(float32 min, float32 max);
private:
    typedef std::vector<BodyGene> Body;
    typedef std::vector<WheelGene> Wheels;
    double score_;
    double timeAlive_;
    b2Vec2 startPosition_;
    float32 initLength_;
    Qt::GlobalColor color_;
    Body body_;
    Wheels wheels_;
};

#endif // CAR_H
