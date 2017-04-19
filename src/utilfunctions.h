#ifndef UTILFUNCTIONS
#define UTILFUNCTIONS

#include <Box2D/Box2D.h>

#endif // UTILFUNCTIONS

///
/// \brief The ShapeCreation struct is used to create b2Shape for Element object
///
struct ShapeCreation
{
    ~ShapeCreation() = default;
    ShapeCreation() = default;
    ShapeCreation(const ShapeCreation &other) = delete;


    ///
    /// \brief Creates polygon shape with vertices on heap.
    /// \remarks b2Shape object is allocated with new operator and should be freed.
    /// \param vertices Pointer to array, which contains vertices for polygon
    /// \param size The size of array
    /// \return Newly created polygon shape on heap
    ///
    b2Shape* operator()(const b2Vec2 *vertices, int32 size) const;

    ///
    /// \brief Creates polygon shape and set is as box with size on heap.
    /// \remarks b2Shape object is allocated with new operator and should be freed.
    /// \param size The size of the box
    /// \return Newly created polygon shape on heap
    ///
    b2Shape* operator()(const b2Vec2 &size) const;

    ///
    /// \brief Creates circle shape of radius size r on heap.
    /// \remarks b2Shape object is allocated with new operator and should be freed.
    /// \param r The radius of the circle
    /// \return Newly created polygon shape on heap
    ///
    b2Shape* operator()(float32 r) const;
};

///
/// \brief The VertexCalculation struct is used to calculate vertex based on angle
/// and length from other vertex.
///
struct VertexCalculation
{
    ~VertexCalculation() = default;
    VertexCalculation() = default;
    VertexCalculation(const VertexCalculation &other) = delete;

    ///
    /// \brief Creates vertex based on angle and length from other vertex.
    /// \param vertex Vertex, which is used to calculate position of the new vertex
    /// \param angle The angle created and passed by parameter vertices
    /// \param length The length of vertex from point (0,0)
    /// \return Newly created vertex
    ///
    b2Vec2 operator()(const b2Vec2& vertex,
                      float32 angle, float32 length) const;
private:
    ///
    /// \brief calcVertex Calc vertex, which with centerVertex creates side of
    /// the traingle. This side is inclined at angle to
    /// side between center vertex and vertex2.
    ///
    /// \param centerVertex Vertex shared with two sides.
    /// \param angle Angle between two sides of body's part in center.
    /// \param length Length of side between calculated vertex and center vertex.
    /// \return Calculated vertex.
    ///
    b2Vec2 calcVertex(const b2Vec2& centerVertex,
                      const b2Vec2& vertex2,
                      float32 angle, float32 length) const;
    ///
    /// \brief calcPoint Calc point, which is rotated by angle around
    /// point (0,0).
    /// \param point Point, which will be rotate.
    /// \param angle Angle of rotation.
    /// \return Rotated point.
    ///
    b2Vec2 calcPoint(const b2Vec2& point, float32 angle) const;

    ///
    /// \brief calcPoint Calc point, which is rotated by angle around
    /// center point.
    /// \param centerPoint Center of rotation.
    /// \param rotatePoint Point, which will be rotate.
    /// \param angle Angle of rotation.
    /// \return Rotated point.
    ///
    b2Vec2 calcPoint(const b2Vec2& centerPoint,
                     const b2Vec2& rotatePoint,
                     float32 angle) const;

    /// Calc parameter a and b, which creates line y = a * x + b
    /// intersects two points.s
    /// b2Vec2::x = a
    /// b2Vec2::y = b
    b2Vec2 calcLine(const b2Vec2& point1,
                    const b2Vec2& point2) const;
    /// Is rotatePoint to the right of center point
    /// @return True if is on right, otherwise false
    bool isOnRight(const b2Vec2& centerPoint,
                   const b2Vec2& rotatePoint) const
        { return rotatePoint.x > centerPoint.x; }
    ///
    /// \brief calcPointInLine Calc point in line, which creates
    /// section with other point of length.
    /// \param line Line parameters (a,b). Line y = a * x + b.
    /// \param point Point, which creates section with calculated point
    /// \param length Section length between points.
    /// \param onRight Determines if calculated point is on the right
    /// or on the left of point
    /// \return Calculated point.
    ///
    b2Vec2 calcPointInLine(const b2Vec2& line,
                           const b2Vec2& point,
                           float32 length, bool onRight) const;
};

///
/// \brief The AngleCalculation struct is used to calculate angle based on two points.
///
struct AngleCalculation
{
    ~AngleCalculation() = default;
    AngleCalculation() = default;
    AngleCalculation(const AngleCalculation &other) = delete;

    ///
    /// \brief Calculates angle between two points, with center in (0,0).
    /// \param point1 The first point
    /// \param point2 The second point
    /// \return Calcualted angle between two points, with center in (0,0)
    ///
    float32 operator()(const b2Vec2 &point1, const b2Vec2 &point2);

    ///
    /// \brief Calculates angle between point and x-axis.
    /// \param point The point
    /// \return Calculated angle between point and x-axis
    ///
    float32 operator()(const b2Vec2 &point);
};

///
/// \brief The ShapeCloning struct is used to clone b2Shape object.
///
struct ShapeCloning
{
    ~ShapeCloning() = default;
    ShapeCloning() = default;
    ShapeCloning(const ShapeCloning &other) = delete;

    ///
    /// \brief Clones b2Shape object.
    /// \remarks b2Shape object is allocated with new operator and should be freed.
    /// \param shape The shape to be cloned.
    /// \return Newly created shape on heap
    ///
    b2Shape *operator()(const b2Shape *shape);
};
