#ifndef ELEMENT_H
#define ELEMENT_H

#include <memory>
#include <vector>
#include <Box2D/Box2D.h>
#include <QWidget>
#include <QPainter>

class Element
{
public:
    struct Parameters
    {
        static const int MAX_DENSITY;
        static const double MAX_FRICTION;
        static const double MAX_RESTITUTION;
        float32 density;
        float32 friction;
        float32 restitution;

        Parameters(float32 d, float32 f, float32 r):
            density(d), friction(f), restitution(r) {}
        Parameters(const Parameters&) = default;
        static Parameters createRandom();
    };

public:
    /// Creates a fixture definition for gene
    /// It does not create a body, fixture definitions and fixtures
    Element(const b2Vec2& position, const b2BodyType& bodyType,
            const Qt::GlobalColor& color);
    virtual ~Element() = default;

    /// Create body and fixture and attach to the world
    /// First you need to add fixtures definitions
    void create(b2World& world);
    void destroy(b2World& world);
    /// Get body position, set color, thickness and call drawElement method
    void draw(QPainter& painter) const;
    /// Add fixture definition
    void addFixture(const b2FixtureDef& fixtureDef);
    /// Create fixture definition with shape and add it
    void addFixture(b2Shape* shape);
    /// Create fixture defintion with shape and parameters and add it.
    void addFixture(b2Shape* shape, const Parameters& parameters);

    b2Body* getBody();

private:
    virtual void drawElement(QPainter& painter,
                             const b2Vec2& position,
                             const float32 angle,
                             const b2Shape* shape) const = 0;
private:
    b2Body* body_;
    b2BodyDef bodyDef_;
    typedef std::vector<b2FixtureDef> FixtureDefs;
    FixtureDefs fixtureDefs_;
    Qt::GlobalColor color_;
};

#endif // ELEMENT_H
