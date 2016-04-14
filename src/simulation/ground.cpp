#include "ground.h"
#include "element/box.h"

Ground::Ground()
{

}

void Ground::initialize(std::vector<ElementPtr>& elements)
{
    elements.push_back(ElementPtr(new Box(0, 10, 1)));
    for (int i = 1; i < 100; i++)
    {
        float32 angle = rand() % 90 - 45;
        float32 width = rand() % 20 + 10;
        Box& box = dynamic_cast<Box&>(*elements[i-1]);
        elements.push_back(ElementPtr(new Box(box, angle, width)));

    }
//    for (int i = 1; i < 10; i++)
//    {
//        float32 angle = 0;
//        float32 width = 10;
//        Box& box = dynamic_cast<Box&>(*elements[i-1]);
//        elements.push_back(ElementPtr(new Box(box, angle, width)));
//    }


}
