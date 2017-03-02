#ifndef BOX_H
#define BOX_H

#include <array>
#include <Box2D/Box2D.h>
#include "polygon.h"

/**
 * @brief The Box class Objects of this class create ground
 */

class Box: public Polygon
{
public:
    enum Corner
    {
        LEFT_UP = 0,
        LEFT_DOWN = 1,
        RIGHT_UP = 2,
        RIGHT_DOWN = 3
    };

public:
    Box(float32 angle = 0, float32 width = 10,
        float32 height = 0.2);
    Box(const Box& box, float32 angle,
        float32 width = 10);
    //TODO implement swap operator= and swap constructor
    Box(const Box& box) = default;
    Box& operator=(const Box& other);
    Element *clone() const
        { return new Box(*this); }

    b2Vec2 getPosition() const;
    b2Vec2 getVertex(Corner corner) const;

private:
    /// Draw polygon
    void drawElement(QPainter& painter,
                     const b2Vec2& position,
                     const float32 angle,
                     const b2Shape* shape,
                     const b2Vec2& parentPosition) const;
    void swap(Box &other);
    ///
        /// \brief calcPoint Calc point, which creates section with startPoint
        /// and is inclined at angle to line y = startPoint.y;
        /// \param startPoint Creates section with calculated point.
        /// \param angle Angle between line y = startPoint.y and
        /// section between startPoint and calculated point.
        /// \param width Section width between startPoint and calculated point.
        /// \return Calculated point.
        ///
        b2Vec2 calcPoint(b2Vec2 startPoint,
                         float32 angle,
                         float32 width) const;
    ///
    /// \brief calcVertices Calc four vertices, two is shared with previous box
    /// \param box Previous box.
    /// \param angle Angle between line y = (y of previous box right upper point)
    /// and previous box
    /// \param width Width of box.
    /// \return Calculated vertices.
    ///
    b2Vec2* calcVertices(const Box& box,
                         float32 angle,
                         float32 width);
    /// Create first box at position (0,0) and parallel to line y = 0.
    b2Vec2* initializeFirst(float32 angle,
                            float32 width,
                            float32 height);
private:
    b2Vec2 position_;
    std::array<b2Vec2,4> vertices_;
};

typedef Box::Corner Corner;

#endif // BOX_H
