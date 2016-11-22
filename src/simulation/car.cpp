#include "car.h"
#include "element/element.h"
#include "element/wheel.h"
#include "element/polygon.h"
#include "utilfunctions.h"

#include <iostream>

using namespace std;

Car::Car(b2Vec2 position): score_(0), timeAlive_(0)
{
    color_ = Qt::GlobalColor::red;
    int maxLength = (BodyGene::MAX_LENGTH - 1) * 100;
    initLength_ = static_cast<float>(1 + std::rand() % maxLength) / maxLength;
    initLength_ *= (BodyGene::MAX_LENGTH - 1);
    initLength_ += 1;

    startPosition_ = position;

    // Car project -- for test
    b2Vec2 prevVertex(0, 0);
    prevVertex += b2Vec2(initLength_, 0);
    int restAngle = 360;
    while(restAngle >= 1)
    {
        int scale = 2;
        int minAngle = 20;
        if(restAngle < 90)
            scale = 1;
        if(minAngle >= restAngle)
            minAngle = 0;
        int angle = minAngle + std::rand() % (restAngle/scale - minAngle);
        if(angle < 2)
            angle = restAngle;
        if(restAngle < 20) angle = restAngle;
        restAngle -= angle;
        float32 length = static_cast<float>(1 + std::rand() % maxLength) / maxLength;
        length *= (BodyGene::MAX_LENGTH - 1);
        length += 1;

        Element::Parameters param = Element::Parameters::createRandom();
        b2Vec2 vertex = VertexCalculation()(prevVertex, angle, length);
        prevVertex = vertex;
        body_.push_back(BodyGene(param, vertex));
    }

    for(int i = 1; i <= 2; ++i)
    {
        Element::Parameters param = Element::Parameters::createRandom();
        int radius = 1 + std::rand() % (WheelGene::MAX_RADIUS - 1);
        int vertexNumber = std::rand() % body_.size();
        wheels_.push_back(WheelGene(radius, vertexNumber, param));
    }
}

Car::Car(const Car &other):
    score_(0), timeAlive_(0), startPosition_(other.startPosition_),
    initLength_(other.initLength_), color_(other.color_)
{

}

Car::Car(const Car &other, const WheelGene &gene, size_t geneIndex):
    score_(0), timeAlive_(0), startPosition_(other.startPosition_),
    initLength_(other.initLength_), color_(other.color_)
{
    if(geneIndex >= other.body_.size())
        throw "Out of body";

    for(const auto & b: other.body_)
    {
        body_.push_back(b);
    }
    size_t i = 0;
    for(const auto & wheel: other.wheels_)
    {
        if(geneIndex == i)
        {
            wheels_.push_back(gene);
            continue;
        }

        wheels_.push_back(wheel);
        ++i;
    }
}

Car::Car(const Car &other, const BodyGene &gene, size_t geneIndex):
    score_(0), timeAlive_(0), startPosition_(other.startPosition_),
    initLength_(other.initLength_), color_(other.color_)
{
    if(geneIndex >= other.body_.size())
        throw "Out of body";

    size_t i = 0;
    for(const auto & b: other.body_)
    {
        if(geneIndex == i)
        {
            body_.push_back(gene);
            continue;
        }
        body_.push_back(b);
        ++i;
    }
    for(const auto & wheel: other.wheels_)
    {
        wheels_.push_back(wheel);
    }
}

Car::Car(const Car &first, const Car &second,
         const std::vector<float32> &angles)
{
    if(angles.back() != 360) throw "Last element must be equal 360";

    size_t firstJ = 0;
    size_t secondJ = 0;
    for(size_t i = 0; i < angles.size(); ++i)
    {
        const Car &parent = i % 2 ? first : second;
        size_t &parentJ = i % 2 ? firstJ : secondJ;
        const Car &notParent = i % 2 ? second : first;
        size_t &notParentJ = i % 2 ? secondJ : firstJ;
        float32 angle = angles[i];

        float32 vertexAngle;
        while(vertexAngle <= angle)
        {
            body_.push_back(parent.body_[parentJ]);
            vertexAngle = AngleCalculation()(parent.body_[parentJ].getVertex());
            parentJ++;
        }
        if( angle == 360 )
            continue;

        //Find first bodyGene, which vertex angle from x-axis is greater then
        //last pushed
        angle = vertexAngle + 5; // 5 - next angle must be min greater than vertexAngle
        vertexAngle = 0;
        while(vertexAngle < angle)
        {
            body_.push_back(notParent.body_[notParentJ]);
            vertexAngle = AngleCalculation()(notParent.body_[notParentJ].getVertex());
            notParentJ++;
        }
        if( (parentJ >= parent.body_.size())
             || (notParentJ >= notParent.body_.size()) )
            throw "Should never get here";
    }

    for(const auto & wheel: first.wheels_)
    {
        wheels_.push_back(wheel);
    }

}

void Car::initialize(std::vector<ElementPtr>& elements)
{
    b2Vec2 vertex;
    vertex.x = initLength_;
    vertex.y = 0;
    // Create car's body
    elements.push_back(ElementPtr(new Polygon(startPosition_,
                                              b2_dynamicBody,
                                              Qt::GlobalColor::red)));

    // Add fixture definitions to body
    for(auto& b: body_)
    {
        elements[0]->addFixture(b.create(vertex),
                                b.getParameters());
        vertex = b.getVertex();
    }

    // Create wheels
    for(auto& w: wheels_)
    {
        vertex = body_[w.getVertexNumber()].getVertex();
        vertex = vertex + startPosition_;
        elements.push_back(w.create(vertex, Qt::GlobalColor::blue));
    }

}

void Car::createJoints(std::vector<ElementPtr> &elements,
                       b2World& world)
{
    b2RevoluteJointDef jointDef;
    b2Vec2 vertex;

    //Create first joint -- for test
    vertex = body_[wheels_[0].getVertexNumber()].getVertex();
    vertex = vertex + startPosition_;
    jointDef.collideConnected = false;
    jointDef.Initialize(elements[1]->getBody(), elements[0]->getBody(), vertex);

    float32 mass = elements[0]->getBody()->GetMass();
    mass+= elements[1]->getBody()->GetMass();
    mass+= elements[2]->getBody()->GetMass();

    jointDef.maxMotorTorque = 4*mass * 80/4;
    jointDef.motorSpeed = elements[1]->getBody()->GetMass() * 200;
    jointDef.enableMotor = true;

    world.CreateJoint(&jointDef);
    // /////////////
    //Create second joint -- for test
    vertex = body_[wheels_[1].getVertexNumber()].getVertex();
    vertex = vertex + startPosition_;
    jointDef.Initialize(elements[2]->getBody(), elements[0]->getBody(), vertex);
    jointDef.motorSpeed = elements[2]->getBody()->GetMass() * 2000;
    world.CreateJoint(&jointDef);
    elements_[1]->getBody()->SetAngularVelocity(-20);
    elements_[2]->getBody()->SetAngularVelocity(-20);
    // /////////////
}

void Car::run(float32 torque)
{
    elements_[1]->getBody()->ApplyTorque(torque, false);
    elements_[2]->getBody()->ApplyTorque(torque, false);
}

void Car::updateObject()
{
    timeAlive_ += 1.0f/60;
}

void Car::calcScore()
{
    b2Body *body = elements_[0]->getBody();
    float32 distance = body->GetPosition().x - startPosition_.x;

    score_ = distance - 2 * timeAlive_;
    if(score_ < 0) score_ = 0;
}
