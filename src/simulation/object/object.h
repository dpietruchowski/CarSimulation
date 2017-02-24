#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <QPainter>
#include <QGraphicsItem>
#include <Box2D/Box2D.h>
#include "simulation/element/element.h"

typedef unsigned int oid;
typedef std::unique_ptr<Element> ElementPtr;
class Object : public QGraphicsItem
{
    static oid ID_;
public:
    Object();
    Object(const Object &other);
    virtual ~Object() = default;
    inline bool operator==(const Object& rhs)
        { return id_ == rhs.id_; }

    void initialize();
    void update(double interval);
    /// Draw all elements using painter
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = Q_NULLPTR);
    void showPos();
    /// Initialize all elements, attach element's bodies
    /// to world, createJoints
    bool create(b2World& world);
    void destroy(b2World& world);

    const b2Vec2& getPosition() const;
    float32 getSpeedX() const;
    float32 getSpeedY() const;
    float32 getSpeed() const;
    bool isMoving() const;
    float32 getRecentSpeed() const;
    oid id() const;
    virtual bool canBeCreated() const { return true; }

protected:
    void advance(int phase);

private:
    void drawId(QPainter *painter) const;
    /// Create elements. After this elements is ready
    /// to attach to world
    virtual void initialize(std::vector<ElementPtr>& elements)= 0;
    virtual void createJoints(std::vector<ElementPtr>& elements,
                              b2World& world)= 0;
    virtual void updateObject(double /* unused */) {}
protected:
    std::vector<ElementPtr> elements_;
    float32 recentSpeed_;
    oid id_;
};

#endif // OBJECT_H
