#ifndef GROUND_H
#define GROUND_H

#include "object.h"
#include "element/element.h"

class Ground: public Object
{
public:
    Ground();

private:
    /// Create 100 box with random angle and width
    void initialize(std::vector<ElementPtr>& genes);
    /// Not implemented yet
    virtual void createJoints(std::vector<ElementPtr>& elements,
                              b2World& world) {}
};

#endif // GROUND_H
