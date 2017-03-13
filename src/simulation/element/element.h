#ifndef ELEMENT_H
#define ELEMENT_H

#include <memory>
#include <vector>
#include <Box2D/Box2D.h>
#include <QWidget>
#include <QPainter>

///
/// \brief The Element class that represents part of object.
/// This class is used to drawing and simulation. It keeps
/// b2Body object used in b2World simulation.
///
class Element
{
public:
    ///
    /// \brief Colide group index. All elements fixtures with this group will
    /// colide with each other.
    ///
    static const int COLIDE_GROUP = 4;
    ///
    /// \brief Dont colide group index. All elements fixtures with this group
    /// wont colide with each other.
    ///
    static const int DONT_COLIDE_GROUP = -4;

    ///
    /// \brief The Parameters struct that define fixture definition parameters
    /// in box2d simulation.
    ///
    struct Parameters
    {
        static const int MAX_DENSITY;        ///< Maximum value of density
        static const double MAX_FRICTION;    ///< Maximum value of friction
        static const double MAX_RESTITUTION; ///< Maximum value of restitution
        float32 density;       ///< Value of density
        float32 friction;      ///< Value of friction
        float32 restitution;   ///< Value of restitution

        ///
        /// \brief A Parameters constructor. Creates object with density,
        /// friction and restitution.
        /// \param density Value of density
        /// \param friction Value of friction
        /// \param restitution Value of restitution
        ///
        Parameters(float32 density, float32 friction, float32 restitution);
        Parameters(const Parameters&) = default;

        ///
        /// \brief Static function to create object with random value of class
        /// members.
        /// \return Newly created object
        ///
        static Parameters createRandom();

        ///
        /// \brief Returns string representation of this object.
        /// \return String representation of this object
        ///
        std::string toString() const;
    };

public:
    ///
    /// \brief An Element constructor. Creates object with position and body
    /// definition. It does not create a body and fixture definitions.
    /// \param position Element position
    /// \param bodyType Element body type
    /// \param color Element color
    ///
    Element(const b2Vec2& position,
            const b2BodyType& bodyType,
            const Qt::GlobalColor& color);

    ///
    /// \brief An Element copy constructor. Creates a copy of other object. It
    /// does deep copy of all the fixture definitions.
    /// \param other Element to be copied
    ///
    Element(const Element &other);

    ///
    /// \brief An Element destructor. Deletes all shape objects, which belongs
    /// to fixture definitions.
    ///
    virtual ~Element();
    virtual Element *clone() const = 0;

    /// Create body and fixture and attach to the world
    /// First you need to add fixtures definitions

    ///
    /// \brief Creates a body and the fixtures (for all fixture definitions)
    /// and attaches to the world. First you need to add fixtures definitions.
    /// \param world The world that body will be attached to
    ///
    void create(b2World& world);

    ///
    /// \brief Destroys a body from world. Body is no longer available.
    /// \param world The world that body will be destoryed from
    ///
    void destroy(b2World& world);

    ///
    /// \brief draw Draws element for all fixture definitions. Elements are
    /// drawn around point (0, 0), which is center of object that they
    /// belongs to. Parent position is needed to define position of drawing,
    /// which is relative to parent position.
    /// \param painter Painter used to draw element.
    /// \param parentPosition The position of parent object, which element
    ///                       belongs to
    ///
    void draw(QPainter &painter, const b2Vec2 &parentPosition) const;

    ///
    /// \brief Adds fixture definition.
    /// \param fixtureDef The fixture definition
    ///
    void addFixture(const b2FixtureDef &fixtureDef);

    ///
    /// \brief Creates fixture definition with shape and adds it.
    /// \param shape The fixture definition shape
    ///
    void addFixture(b2Shape *shape);

    ///
    /// \brief Creates fixture defintion with shape and parameters and adds it.
    /// \param shape The fixture definition shape
    /// \param parameters The fixture definition parameters
    ///
    void addFixture(b2Shape *shape, const Parameters &parameters);

    ///
    /// \brief Sets group index to all fixture definitions to be COLIDE_GROUP or
    /// DONT_COLIDE_GROUP. Must be invoke before create() funtion.
    /// \param c @c true if element should collide, otherwise @c false
    ///
    void collide(bool c);

    ///
    /// \brief Saves body angle and position. This function is needed for
    /// drawing element if body do not exist (was removed).
    ///
    void update();

    ///
    /// \brief Returns pointer to element's body.
    /// \return Element's body
    ///
    b2Body *getBody() const;

    ///
    /// \brief Returns pointer to element's shape.
    /// \return Element's shape
    ///
    const b2Shape *getShape() const;

    ///
    /// \brief Returns element's position of drawing. It is body's position
    /// saved in update() function.
    /// \return Element's position of drawing
    ///
    const b2Vec2 &getDrawPoisiton() const;

protected:
    void swap(Element &other);

private:
    virtual void drawElement(QPainter &painter,
                             const b2Vec2 &position,
                             const float32 angle,
                             const b2Shape *shape,
                             const b2Vec2 &parentPosition) const = 0;
private:
    b2Body *body_;
    b2BodyDef bodyDef_;
    typedef std::vector<b2FixtureDef> FixtureDefs;
    FixtureDefs fixtureDefs_;
    Qt::GlobalColor color_;
    b2Vec2 drawPosition_;
    float32 drawAngle_;
};

#endif // ELEMENT_H
