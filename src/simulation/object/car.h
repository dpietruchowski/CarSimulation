#ifndef CAR_H
#define CAR_H

#include "object.h"
#include "simulation/element/element.h"
#include "genetic/gene/bodygene.h"
#include "genetic/gene/wheelgene.h"

#include <vector>

class Car;

///
/// \brief The unique pointer to Car object.
///
typedef std::unique_ptr<Car> CarPtr;

///
/// \brief The shared pointer to Car object.
///
typedef std::shared_ptr<Car> CarSPtr;

///
/// \brief The vector of CarPtr objects.
///
typedef std::vector<CarPtr> Objects;

Q_DECLARE_METATYPE(CarSPtr);

///
/// \brief The Car class that represents car in simulation. Objects of this class
/// are used to evolution. The important of this object are body genes.
/// Every body gene keeps vertex in local coordinates. For all vertices can be
/// calculated angle from x-axis and they can be sorted. Body consists triangle
/// elements with 3 vertices, which is 2 nearest outside vertices and center
/// point (0, 0). To outside vertices can be attached wheels. This vertices are
/// hold in wheel genes.
///
class Car: public Object
{
public:
    ///
    /// \brief A Car constructor. Creates object with position and random created
    /// genes.
    /// \param position The car position
    ///
    Car(b2Vec2 position);

    ///
    /// \brief A Car copy constructor. Score and time alive value are set to 0.
    /// \remarks A copy constructor of base class (Object) is not called.
    /// Elements are not cloned.
    /// \param other A car to be copied
    ///
    Car(const Car &other);

    ///
    /// \brief A Car copy constructor with parameter which tells whether score
    /// and time alive should be reset
    /// \param other A car to be copied
    /// \param resetScore A parameter which tells whether score and time alive
    /// should be set to 0.
    ///
    Car(const Car &other, bool resetScore);

    ///
    /// \brief A Car wheel mutation constructor. Creates copy of other car and
    /// swaps one wheel gene with gene.
    /// \param other A car to be mutated
    /// \param gene New wheel gene
    /// \param geneIndex Wheel gene index to be replaced
    ///
    Car(const Car &other, const WheelGene &gene, size_t geneIndex);

    ///
    /// \brief A Car body mutation constructor. Creates copy of other car and
    /// swaps first body gene, which vertex has greater angle.
    /// \param other A car to be mutated
    /// \param gene New body gene
    ///
    Car(const Car &other, const BodyGene &gene);

    ///
    /// \brief A Car crossover constructor. Angles define where are crossover
    /// points. Crossover point is first body gene, which vertex angle
    /// is greater than angle in vector.
    /// \param first First car parent to crossover
    /// \param second Second car parent to crossover
    /// \param angles Angles which define crossover points
    ///
    Car(const Car &first, const Car &second,
        const std::vector<float32> &angles);

    ///
    /// \brief A Car crossover constructor. Creates car with body gene from
    /// first car parent and with wheel gene from second car parent.
    /// \param first First car parent to crossover
    /// \param second Second car parent to crossover
    ///
    Car(const Car &first, const Car &second);

    ///
    /// \brief operator == Compares car's scores.
    /// \param rhs Car to compare
    /// \return @c true if car's scores are equal, otherwise @c false
    ///
    inline bool operator==(const Car& rhs);

    ///
    /// \brief operator != Compares car's scores.
    /// \param rhs Car to compare
    /// \return @c true if car's scores are not equal, otherwise @c false
    ///
    inline bool operator!=(const Car& rhs);

    ///
    /// \brief operator < Compares car's scores.
    /// \param rhs Car to compare
    /// \return @c true if this score is lower than rhs's score,
    /// otherwise @c false
    ///
    inline bool operator< (const Car& rhs);

    ///
    /// \brief operator > Compares car's scores.
    /// \param rhs Car to compare
    /// \return @c true if this rhs's score is lower than this score,
    /// otherwise @c false
    ///
    inline bool operator> (const Car& rhs);

    ///
    /// \brief operator <= Compares car's scores.
    /// \param rhs Car to compare
    /// \return @c true if this score is lower than or equal to rhs's score,
    /// otherwise @c false
    ///
    inline bool operator<=(const Car& rhs);

    ///
    /// \brief operator >= Compares car's scores.
    /// \param rhs Car to compare
    /// \return @c true if rhs's score is lower than or equal to this score,
    /// otherwise @c false
    ///
    inline bool operator>=(const Car& rhs);

    ///
    /// \brief Returns car's score.
    /// \return Car's score
    ///
    double score() const { return score_; }

    ///
    /// \brief Returns the time of cars life in miliseconds.
    /// \return Time of cars life in miliseconds
    ///
    double timeAlive() const { return timeAlive_; }

    ///
    /// \brief Query if car is moved.
    /// \param interval  The time elapsed since the last update
    /// \return @c true if car is moved, otherwise false
    ///
    bool isMoved(double interval) const;

    ///
    /// \brief Returns number of body's elements.
    /// \return Number of body's elements
    ///
    size_t bodySize() const;

    ///
    /// \brief Calculate the car's score. This function must be executed before
    /// deleted from b2World (b2Body must not be freed).
    ///
    void calcScore();

    ///
    /// \brief Returns car's string representation.
    /// \return Car's string representation
    ///
    std::string toString() const;

    ///
    /// \brief Query if vertex can be set in the new body's element.
    /// \param vertex New body's vertex
    /// \return @c true if vertex is valid, otherwise @c false
    ///
    bool isVertexSettable(const b2Vec2 &vertex) const;

    ///
    /// \brief Query if car is valid and can be created and added to b2World.
    /// \return @c true if car is valid, otherwise @c false
    ///
    bool canBeCreated() const;

    ///
    /// \brief Reimplemented method. Defines the outer bounds of the ground
    /// as a rectangle.
    /// \return The outer bounds of the ground as a rectangle
    ///
    QRectF boundingRect() const;

    ///
    /// \brief Query if car is crashed.
    /// \return @c true if car is crashed, otherwise @c false
    ///
    bool isCrashed() const;

    ///
    /// \brief Invokes a base class initialize method to creating simulation
    /// elements based on genes.
    ///
    void initialize();

private:
    void copyGenes(const Car &other);
    void initialize(std::vector<ElementPtr>& elements);
    void createJoints(std::vector<ElementPtr>& elements,
                      b2World& world);
    void updateObject(double interval);
    float32 rand(float32 min, float32 max);
    float32 randLength() const;
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
