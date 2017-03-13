#ifndef GROUND_H
#define GROUND_H

#include "object.h"
#include "simulation/element/element.h"

///
/// \brief The Ground class that represent ground in simulation.
///
class Ground: public Object
{
public:
    ///
    /// \brief A Ground constructor. Creates ground with size (height and width)
    /// \param size The size of the ground
    ///
    Ground(b2Vec2 size);

    ///
    /// \brief Reimplemented method. Defines the outer bounds of the ground
    /// as a rectangle.
    /// \return The outer bounds of the ground as a rectangle
    ///
    QRectF boundingRect() const;

private:
    /// Create 100 box with random angle and width
    void initialize(std::vector<ElementPtr>& genes);
    /// Not implemented yet
    virtual void createJoints(std::vector<ElementPtr>&,
                              b2World&) {}
    void updateObject(double /* unused */) {}
    b2Vec2 size_;
};

#endif // GROUND_H
