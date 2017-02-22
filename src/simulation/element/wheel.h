#ifndef WHEEL_H
#define WHEEL_H

#include <QWidget>
#include <QPainter>
#include <Box2D/Box2D.h>

#include "element.h"

class Wheel: public Element
{
public:
    Wheel(const b2Vec2& position, float32 r,
          const Qt::GlobalColor& color,
          const Element::Parameters& parameters);
private:
    /// Draw wheel
    void drawElement(QPainter& painter,
                     const b2Vec2& position,
                     const float32 angle,
                     const b2Shape* shape,
                     const b2Vec2& parentPosition) const;
};

#endif // WHEEL_H
