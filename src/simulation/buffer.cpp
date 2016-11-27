#include "buffer.h"

using namespace std;

bool Buffer::push(CarPtr car)
{
    if(full())
        return false;

    buffer_.push_back(move(car));
    return true;
}

CarPtr Buffer::pop()
{
    CarPtr car = move(buffer_.front());
    buffer_.pop_front();

    return move(car);
}

bool Buffer::full() const
{
    return buffer_.size() >= size_;
}

bool Buffer::empty() const
{
    return buffer_.empty();
}
