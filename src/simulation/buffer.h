#ifndef BUFFER_H
#define BUFFER_H

#include <list>

#include "object/car.h"

///
/// \brief The Buffer class is container for cars with defined capacity
///
class Buffer
{
public:
    ///
    /// \brief A Buffer constructor. Creates empty buffer with size.
    /// \param size The buffer capacity
    ///
    Buffer(size_t size): size_(size) {}

    ///
    /// \brief Adds car to the end of the buffer.
    /// \param car The car to be added
    /// \return @c true if car was added, otherwise @c false
    ///
    bool push(CarPtr car);

    ///
    /// \brief Erases front car from buffer and returns it.
    /// \return Erased front car
    ///
    CarPtr pop();

    ///
    /// \brief Returns car's reference from front.
    /// \return Car's reference from front
    ///
    CarPtr& front();

    ///
    /// \brief Returns car's reference from back.
    /// \return Car's reference from back
    ///
    CarPtr& back();

    ///
    /// \brief Query if buffer is full.
    /// \return @c true if buffer is full, otherwise @c false
    ///
    bool full() const;

    ///
    /// \brief Returns actual size of buffer.
    /// \return Actual size of buffer
    ///
    size_t size() const;

    ///
    /// \brief Query if buffer is empty.
    /// \return @c true if buffer is empty, otherwise @c false
    ///
    bool empty() const;

    ///
    /// \brief Returns max size of buffer.
    /// \return Max size of buffer
    ///
    size_t maxSize() const;

private:
    typedef std::list<CarPtr> Container;
    Container buffer_;
    size_t size_;
};

#endif // BUFFER_H
