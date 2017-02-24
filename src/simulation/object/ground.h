#ifndef GROUND_H
#define GROUND_H

#include "object.h"
#include "simulation/element/element.h"

class Ground: public Object
{
public:
    Ground(b2Vec2 size);
    QRectF boundingRect() const;

private:
    /// Create 100 box with random angle and width
    void initialize(std::vector<ElementPtr>& genes);
    /// Not implemented yet
    virtual void createJoints(std::vector<ElementPtr>&,
                              b2World&) {}
    b2Vec2 size_;
};

#endif // GROUND_H
