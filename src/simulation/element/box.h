#ifndef BOX_H
#define BOX_H

#include <array>
#include <Box2D/Box2D.h>
#include "polygon.h"

///
/// \brief The Box class that is part of ground object
///
class Box: public Polygon
{
public:
    ///
    /// \brief The Corner enum for all vertices of the box object.
    ///
    enum Corner
    {
        LEFT_UP = 0,    ///< Left upper corner
        LEFT_DOWN = 1,  ///< Left bottom corner
        RIGHT_UP = 2,   ///< Right upper corner
        RIGHT_DOWN = 3  ///< Right bottom corner
    };

public:
    ///
    /// \brief A Box constructor. Creates box with angle, width and height.
    /// \param angle The value of angle
    /// \param width The value of width
    /// \param height The value of height
    ///
    Box(float32 angle = 0, float32 width = 10,
        float32 height = 0.2);

    ///
    /// \brief A Box constructor. Creates box based on previous with whom it
    /// will be connected.
    /// \param previous The previous box
    /// \param angle The value of angle
    /// \param width The value of width
    ///
    Box(const Box &previous, float32 angle,
        float32 width = 10);
    Box(const Box& box) = default;

    ///
    /// \brief Creates copy of other and swaps with this box
    /// \param other Box to be copied
    /// \return Reference to this box
    ///
    Box &operator=(const Box &other);

    ///
    /// \brief Creates copy of this box.
    /// \return Copy of this box
    ///
    Element *clone() const;

    ///
    /// \brief Returns box position.
    /// \return Box position
    ///
    b2Vec2 getPosition() const;

    ///
    /// \brief Returns vertex position.
    /// \param corner Position of this vertex will be returned
    /// \return Vertex position
    ///
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
