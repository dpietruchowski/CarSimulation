#ifndef BUFFER_H
#define BUFFER_H

#include <list>

#include "car.h"

class Buffer
{
public:
    Buffer(size_t size): size_(size) {}

    bool push(CarPtr car);
    CarPtr pop();
    bool full() const;
    bool empty() const;

private:
    typedef std::list<CarPtr> Container;
    Container buffer_;
    size_t size_;
};

#endif // BUFFER_H
