#include "ground.h"
#include "simulation/element/box.h"
#include <math.h>
#include <iostream>
#include <memory>

using namespace std;

Ground::Ground(b2Vec2 size): size_(size)
{

}

QRectF Ground::boundingRect() const
{
    return QRectF(-20, -20, size_.x+20, size_.y+20);
}

void Ground::initialize(std::vector<ElementPtr>& elements)
{
    elements.push_back(ElementPtr(new Box(0, 10, 1)));
    float32 length = 0;
    int i = 1;
    float32 threshold = 1.f;
    while(abs(length - size_.x) > threshold)
    {
        float32 angle = rand() % 90 - 45;
        float32 width = rand() % 20 + 10;
        Box& box = dynamic_cast<Box&>(*elements[i-1]);

        Box nextBox(box, angle, width);
        length = nextBox.getPosition().x + nextBox.getVertex(Corner::RIGHT_UP).x;
        if ((length - size_.x) > threshold)
        {
            float32 angleRad = (angle * M_PI) / 180.f;
            float32 restLength = abs(nextBox.getPosition().x - size_.x);
            width = restLength / cos(angleRad);
            nextBox = Box(box, angle, width);
            length = nextBox.getPosition().x + nextBox.getVertex(Corner::RIGHT_UP).x;
        }

        float32 height = nextBox.getPosition().y + nextBox.getVertex(Corner::RIGHT_UP).y;
        if ( (height > size_.y/2) || (height < -size_.y/2) )
        {
            angle = 0 - angle;
            nextBox = Box(box, angle, width);
            length = nextBox.getPosition().x + nextBox.getVertex(Corner::RIGHT_UP).x;
        }

        elements.push_back(ElementPtr(new Box(nextBox)));
        ++i;

//        Box& nextBox = dynamic_cast<Box&>(*elements[i-1]);
//                cout << "::: GROUND BOX :::" << endl;
//                cout << "position: " << nextBox.getPosition().x
//                     << " " << nextBox.getPosition().y << endl;
//                cout << "left_up: " << nextBox.getVertex(Corner::LEFT_UP).x
//                     << " " << nextBox.getVertex(Corner::LEFT_UP).y << endl;
//                cout << "left_down: " << nextBox.getVertex(Corner::LEFT_DOWN).x
//                     << " " << nextBox.getVertex(Corner::LEFT_DOWN).y << endl;
//                cout << "right_up: " << nextBox.getVertex(Corner::RIGHT_UP).x
//                     << " " << nextBox.getVertex(Corner::RIGHT_UP).y << endl;
//                cout << "right_down: " << nextBox.getVertex(Corner::RIGHT_DOWN).x
//                     << " " << nextBox.getVertex(Corner::RIGHT_DOWN).y << endl;
    }
//    for (int i = 1; i < 10; i++)
//    {
//        float32 angle = 0;
//        float32 width = 10;
//        Box& box = dynamic_cast<Box&>(*elements[i-1]);
//        elements.push_back(ElementPtr(new Box(box, angle, width)));
//    }


}
