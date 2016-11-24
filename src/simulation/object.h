#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <QPainter>
#include <Box2D/Box2D.h>
#include "element/element.h"

typedef std::unique_ptr<Element> ElementPtr;
class Object
{
public:
    Object();
    virtual ~Object() = default;

    void update(double interval);
    /// Draw all elements using painter
    void draw(QPainter& painter) const;
    /// Initialize all elements, attach element's bodies
    /// to world, createJoints
    void create(b2World& world);
    void destroy(b2World& world);

    const b2Vec2& getPosition() const;
    float32 getSpeedX() const;
    float32 getSpeedY() const;
    float32 getSpeed() const;
    bool isMoving() const;

private:
    /// Create elements. After this elements is ready
    /// to attach to world
    virtual void initialize(std::vector<ElementPtr>& elements)= 0;
    virtual void createJoints(std::vector<ElementPtr>& elements,
                              b2World& world)= 0;
    virtual void updateObject(double /* unused */) {}
protected:
    std::vector<ElementPtr> elements_;
    float32 recentSpeed_;
};

#endif // OBJECT_H
