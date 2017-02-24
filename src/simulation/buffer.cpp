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

CarPtr& Buffer::front()
{
    return buffer_.front();
}

CarPtr& Buffer::back()
{
    return buffer_.back();
}

bool Buffer::full() const
{
    return buffer_.size() >= size_;
}

size_t Buffer::size() const
{
    return buffer_.size();
}

bool Buffer::empty() const
{
    return buffer_.empty();
}

size_t Buffer::maxSize() const
{
    return size_;
}

void Buffer::print(Dialog &console, int number) const
{
    int i = 0;
    console.clear(number);
    if(number == 0)
        for(const auto &b : buffer_)
        {
            stringstream ss;
            ss << "[" << i++ << "] " << b->id();
            console << ss;
        }
    else
        for(const auto &b : buffer_)
        {
            stringstream ss;
            ss << "[" << i++ << "] " << b->id();
            console <= ss;
        }
}
