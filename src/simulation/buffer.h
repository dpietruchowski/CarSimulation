#ifndef BUFFER_H
#define BUFFER_H

#include <list>

#include "object/car.h"

class Buffer
{
public:
    Buffer(size_t size): size_(size) {}

    bool push(CarPtr car);
    CarPtr pop();
    CarPtr& front();
    CarPtr& back();
    bool full() const;
    size_t size() const;
    bool empty() const;
    size_t maxSize() const;

private:
    typedef std::list<CarPtr> Container;
    Container buffer_;
    size_t size_;
};

#endif // BUFFER_H
