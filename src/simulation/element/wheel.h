#ifndef WHEEL_H
#define WHEEL_H

#include <QWidget>
#include <QPainter>
#include <Box2D/Box2D.h>

#include "element.h"

///
/// \brief The Wheel class that represents circle shape.
///
class Wheel: public Element
{
public:
    ///
    /// \brief A Wheel constructor. Creates object with position, radius and
    ///        parameters
    /// \param position The position of the wheel
    /// \param radius The radius of the wheel
    /// \param color The colour of the wheel
    /// \param parameters The parameters of the wheel
    ///
    Wheel(const b2Vec2& position, float32 radius,
          const Qt::GlobalColor& color,
          const Element::Parameters& parameters);
    Wheel() = delete;
    Wheel(const Wheel &other) = default;

    ///
    /// \brief Creates copy of this wheel.
    /// \return Copy of this wheel
    ///
    Element *clone() const;
private:
    /// Draw wheel
    void drawElement(QPainter& painter,
                     const b2Vec2& position,
                     const float32 angle,
                     const b2Shape* shape,
                     const b2Vec2& parentPosition) const;
};

#endif // WHEEL_H
