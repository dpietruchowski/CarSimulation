#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <QPainter>
#include <QGraphicsItem>
#include <Box2D/Box2D.h>
#include "simulation/element/element.h"

///
/// \brief Unsigned int type.
///
typedef unsigned int oid;

///
/// \brief Unique pointer to Element object.
///
typedef std::unique_ptr<Element> ElementPtr;

///
/// \brief The Object class that represents objects in simulation.
///
class Object : public QGraphicsItem
{
private:
    static oid ID_;

public:
    ///
    /// \brief An Object constructor. Creates object with default parameters.
    ///
    Object();

    ///
    /// \brief An Object copy constructor.
    /// \param other
    ///
    Object(const Object &other);
    virtual ~Object() = default;

    ///
    /// \brief operator == . Compares object's ids.
    /// \param rhs Object to compare
    /// \return @c true if ids is equals, otherwise @c false
    ///
    inline bool operator==(const Object& rhs);

    ///
    /// \brief Initializes this object. Creates elements, which this object
    /// contains.
    ///
    void initialize();

    ///
    /// \brief Updates this object. Calls update for all elements. Updates speed
    /// and calls update for derived class.
    /// \param interval The time elapsed since the last update.
    ///
    void update(double interval);

    ///
    /// \brief Reimplemented method used to draw object. This function, which is
    /// usually called by QGraphicsView, paints the contents of an item in local
    /// coordinates.
    /// \param painter Painter used to draw object
    /// \param option The option parameter provides style options for the item,
    /// such as its state, exposed area and its level-of-detail hints
    /// \param widget If provided, it points to the widget that is being
    /// painted on
    ///
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = Q_NULLPTR);


    void showPos();
    /// Initialize all elements, attach element's bodies
    /// to world, createJoints

    ///
    /// \brief Creates object and attachs to world.
    /// \param world The world that body will be attached to
    /// \return @c true if object was created, otherwise @c false
    ///
    bool create(b2World& world);

    ///
    /// \brief Destroys object from world. It destroys all element's bodies.
    /// \param world The world that body will be destoryed from
    ///
    void destroy(b2World& world);

    ///
    /// \brief Returns object position.
    /// \return Object position
    ///
    const b2Vec2& getPosition() const;

    ///
    /// \brief Sets the object position of the object's origin and rotation.
    /// Manipulating a object's position may cause non-physical behavior.
    /// Note: contacts are updated on the next call to b2World::Step.
    /// \param position New object position
    ///
    void setPosition(const b2Vec2 &position);

    ///
    /// \brief Returns the object linear velocity in x direction.
    /// \return The object velocity in x direction
    ///
    float32 getSpeedX() const;

    ///
    /// \brief Returns the object linear velocity in y direction.
    /// \return The object velocity in y direction
    ///
    float32 getSpeedY() const;

    ///
    /// \brief Returns the object linear velocity
    /// \return
    ///
    float32 getSpeed() const;

    ///
    /// \brief Query if object is moving.
    /// \param interval The time interval between updates.
    /// \return @c true if object is moving, otherwise @c false
    ///
    bool isMoving(double interval) const;

    ///
    /// \brief Returns the object's recent speed, which is avaraged value.
    /// \return The object recent speed
    ///
    float32 getRecentSpeed() const;

    ///
    /// \brief Returns the object's id.
    /// \return The object's id
    ///
    oid id() const;

    ///
    /// \brief Query if object  can be created.
    /// \return @c true if object can be created, otherwise @c false
    ///
    virtual bool canBeCreated() const;

protected:
    void advance(int phase);

private:
    void drawId(QPainter *painter) const;
    /// Create elements. After this elements is ready
    /// to attach to world
    virtual void initialize(std::vector<ElementPtr>& elements)= 0;
    virtual void createJoints(std::vector<ElementPtr>& elements,
                              b2World& world)= 0;
    virtual void updateObject(double /* unused */) = 0;
protected:
    std::vector<ElementPtr> elements_;
    float32 recentSpeed_;
    oid id_;
};

#endif // OBJECT_H
