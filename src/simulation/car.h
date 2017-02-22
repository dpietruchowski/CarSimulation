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
    Car(const Car &first, const Car &second);
    inline bool operator==(const Car& rhs)
        { return score_ == rhs.score_; }
    inline bool operator!=(const Car& rhs)
        { return !operator==(rhs); }
    inline bool operator< (const Car& rhs)
        { return score_ < rhs.score_; }
    inline bool operator> (const Car& rhs)
        { return score_ > rhs.score_; }
    inline bool operator<=(const Car& rhs)
        { return !operator> (rhs); }
    inline bool operator>=(const Car& rhs)
        { return !operator< (rhs); }
    void run(float32 torque);
    double score() const { return score_; }
    double timeAlive() const { return timeAlive_; }
    bool isMoved() const { return getPosition().x > startPosition_.x + 2; }
    size_t bodySize() const { return body_.size(); }
    void calcScore();
    std::string toString() const;
    bool isVertexSettable(const b2Vec2 &vertex) const;

private:
    void initialize(std::vector<ElementPtr>& elements);
    void createJoints(std::vector<ElementPtr>& elements,
                      b2World& world);
    void updateObject(double interval);
    float32 rand(float32 min, float32 max);
    float32 randLength() const;
    bool canBeCreated() const;
private:
    typedef std::vector<BodyGene> Body;
    typedef std::vector<WheelGene> Wheels;
    double score_;
    double timeAlive_;
    b2Vec2 startPosition_;
    float32 initLength_;
    Qt::GlobalColor wheelColor_;
    Qt::GlobalColor bodyColor_;
    Body body_;
    Wheels wheels_;
};

#endif // CAR_H
