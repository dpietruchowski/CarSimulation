#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <QWidget>
#include <QPainter>
#include <Box2D/Box2D.h>

#include "element.h"

///
/// \brief The Polygon class that represents polygon shape.
///
class Polygon: public Element
{
public:
    ///
    /// \brief A Polygon constructor. Creates object with position, shape,
    ///        body type and colour.
    /// \param position The polygon's position
    /// \param shape The polygon's shape
    /// \param bodyType The polygon's body type
    /// \param color The polygon's colour
    ///
    Polygon(const b2Vec2& position, b2Shape* shape,
            const b2BodyType& bodyType,
            const Qt::GlobalColor& color);

    ///
    /// \brief A Polygon constructor. Creates object with position, body type
    ///        and colour.
    /// \param position The polygon's position
    /// \param bodyType The polygon's body type
    /// \param color The polygon's colour
    ///
    Polygon(const b2Vec2& position,
            const b2BodyType& bodyType,
            const Qt::GlobalColor& color);
    Polygon() = delete;
    Polygon(const Polygon& other) = default;

    ///
    /// \brief Creates copy of this wheel.
    /// \return Copy of this wheel
    ///
    Element *clone() const;

private:
    /// Draw polygon
    void drawElement(QPainter& painter,
                     const b2Vec2& position,
                     const float32 angle,
                     const b2Shape* shape,
                     const b2Vec2& parentPosition) const;
};

#endif // POLYGON_H
