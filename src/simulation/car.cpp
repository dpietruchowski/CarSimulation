#include "car.h"
#include "element/wheel.h"
#include "element/polygon.h"
#include "utilfunctions.h"

#include <iostream>

Car::Car(b2Vec2 position)
{
    color_ = Qt::GlobalColor::red;
    initLength_ = 6;
    startPosition_ = position;

    // Car project -- for test
    Element::Parameters param({10,1,0.1});
    body_.push_back(BodyGene(20 , 8, param));
    body_.push_back(BodyGene(10 , 6, param));
    param.density = 1;
    body_.push_back(BodyGene(170 , 6, param));
    body_.push_back(BodyGene(30 , 3, param));
    body_.push_back(BodyGene(10 , 6, param));
    body_.push_back(BodyGene(360 - 240, initLength_, param));

    param.density = 20;
    param.friction = 0.5;
    param.restitution = 0.1;
    wheels_.push_back(WheelGene(4, body_.size()-1, param));
    wheels_.push_back(WheelGene(3, body_.size()-2, param));
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

    jointDef.maxMotorTorque = 8*mass * 80/4;
    jointDef.motorSpeed = elements[1]->getBody()->GetMass() * 2000;
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

float32 Car::rand(float32 min, float32 max)
{
    return min + static_cast<float32>(std::rand() % static_cast<int>(max - min));
}
