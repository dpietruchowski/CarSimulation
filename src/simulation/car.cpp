#include "car.h"
#include "element/element.h"
#include "element/wheel.h"
#include "element/polygon.h"
#include "utilfunctions.h"

#include <iostream>

using namespace std;

Car::Car(b2Vec2 position)
{
    color_ = Qt::GlobalColor::red;
    int maxLength = (BodyGene::MAX_LENGTH - 1) * 100;
    initLength_ = static_cast<float>(1 + std::rand() % maxLength) / maxLength;
    initLength_ *= (BodyGene::MAX_LENGTH - 1);
    initLength_ += 1;

    startPosition_ = position;

    // Car project -- for test
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
        if(restAngle < 20) angle = restAngle;
        restAngle -= angle;
        float32 length = static_cast<float>(1 + std::rand() % maxLength) / maxLength;
        length *= (BodyGene::MAX_LENGTH - 1);
        length += 1;
        Element::Parameters param = Element::Parameters::createRandom();
        body_.push_back(BodyGene(angle, length, param));
    }

    for(int i = 1; i <= 2; ++i)
    {
        Element::Parameters param = Element::Parameters::createRandom();
        int radius = 1 + std::rand() % (WheelGene::MAX_RADIUS - 1);
        int vertexNumber = std::rand() % body_.size();
        wheels_.push_back(WheelGene(radius, vertexNumber, param));
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
