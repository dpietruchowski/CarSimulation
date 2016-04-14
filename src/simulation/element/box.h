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
    Box(float32 angle = 0, float32 width = 10,
        float32 height = 0.2);
    Box(const Box& box, float32 angle,
        float32 width = 10);

private:
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
    std::array<b2Vec2,4> vertices_;
    b2Vec2 position_;
};
#endif // BOX_H
