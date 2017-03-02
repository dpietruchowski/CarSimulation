#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <QWidget>
#include <QPainter>
#include <Box2D/Box2D.h>

#include "element.h"

class Polygon: public Element
{
public:
    Polygon(const b2Vec2& position, b2Shape* shape,
            const b2BodyType& bodyType,
            const Qt::GlobalColor& color);

    Polygon(const b2Vec2& position,
            const b2BodyType& bodyType,
            const Qt::GlobalColor& color);
    Polygon() = delete;
    Polygon(const Polygon& other) = default;
    Element *clone() const
        { return new Polygon(*this); }

private:
    /// Draw polygon
    void drawElement(QPainter& painter,
                     const b2Vec2& position,
                     const float32 angle,
                     const b2Shape* shape,
                     const b2Vec2& parentPosition) const;
};

#endif // POLYGON_H
