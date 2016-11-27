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
    initLength_ = randLength();

    startPosition_ = position;

    //TODO Move this to private function;
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
        float32 length = randLength();

        Element::Parameters param = Element::Parameters::createRandom();
        b2Vec2 vertex = VertexCalculation()(prevVertex, angle, length);
        prevVertex = vertex;
        body_.push_back(BodyGene(param, vertex));
    }

    for(int i = 1; i <= 2; ++i)
    {
        Element::Parameters param = Element::Parameters::createRandom();
        int maxRadius = (WheelGene::MAX_RADIUS - 1) * 100;
        float32 radius = static_cast<float>(1 + std::rand() % maxRadius) / maxRadius;
        radius *= (WheelGene::MAX_RADIUS - 1);
        radius += 0.5;
        int vertexNumber = std::rand() % body_.size();
        wheels_.push_back(WheelGene(radius, vertexNumber, param));
    }
}

Car::Car(const Car &other):
    score_(0), timeAlive_(0), startPosition_(other.startPosition_),
    initLength_(other.initLength_), color_(other.color_)
{
    for(const auto & b: other.body_)
    {
        body_.push_back(b);
    }
    for(const auto & wheel: other.wheels_)
    {
        wheels_.push_back(wheel);
    }
}

Car::Car(const Car &other, const WheelGene &gene, size_t geneIndex):
    Car(other)
{
    if(geneIndex >= other.body_.size())
        throw "Out of body";

    WheelGene wheel(gene);
    std::swap(wheels_[geneIndex], wheel);
}

Car::Car(const Car &other, const BodyGene &gene):
    Car(other)
{
    if( !isVertexSettable(gene.getVertex()) )
        throw "wrong gene";
    //TODO Move this to private function;
    float32 geneAngle = AngleCalculation()(gene.getVertex());
    Body::iterator prevIt = body_.begin();
    for(Body::const_iterator it = other.body_.begin() + 1;
        it != other.body_.end(); ++it)
    {
        float32 angle = AngleCalculation()(it->getVertex());
        if(angle > geneAngle)
        {
            BodyGene bodyPart(gene);
            std::swap(*prevIt, bodyPart);
            break;
        }
        ++prevIt;
    }
}

Car::Car(const Car &first, const Car &second,
         const std::vector<float32> &angles):
    score_(0), timeAlive_(0), startPosition_(first.startPosition_),
    initLength_(first.initLength_), color_(first.color_)
{
    //TODO Move this to private function;
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

        float32 vertexAngle = 0;
        while( (vertexAngle < angle) && (parentJ < parent.body_.size()) )
        {
            body_.push_back(BodyGene(parent.body_[parentJ]));
            vertexAngle = AngleCalculation()(parent.body_[parentJ].getVertex());
            parentJ++;
        }

        if( (angle == 360) || (parentJ >= parent.body_.size()) )
            break;

        //Find first bodyGene, which vertex angle from x-axis is greater then
        //last pushed
        angle = vertexAngle + 0.5; // 5 - next angle must be min greater than vertexAngle
        vertexAngle = 0;
        while((vertexAngle < angle) && (notParentJ < notParent.body_.size()))
        {
            vertexAngle = AngleCalculation()(notParent.body_[notParentJ].getVertex());
            notParentJ++;
        }
    }

    //TODO This wheels could have indexNumber which is now longer avaiable
    //(body_.size is smaller thank before)
    for(const auto & wheel: first.wheels_)
    {
        wheels_.push_back(WheelGene(wheel, body_.size()));
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

void Car::updateObject(double interval)
{
    timeAlive_ += 1.0/60;
}

float32 Car::randLength() const
{
    int max = BodyGene::MAX_LENGTH;
    int min = BodyGene::MIN_LENGTH;
    float32 length = (double)std::rand() / RAND_MAX;;
    length *= (max - min);
    length += min;

    return length;
}

void Car::calcScore()
{
    b2Body *body = elements_[0]->getBody();
    float32 distance = body->GetPosition().x - startPosition_.x;

    score_ = distance - 2 * timeAlive_;
    if(score_ < 0) score_ = 0;
}

string Car::toString() const
{
    string sCar;

    sCar += to_string(score_) + " ";
    sCar += to_string(timeAlive_) + " ";
    sCar += to_string(startPosition_.x) + " ";
    sCar += to_string(startPosition_.y) + " ";
    sCar += to_string(initLength_) + "\n";
    for(const auto & b: body_)
    {
        sCar += "BG: " + b.toString() + "\n";
    }
    for(const auto & wheel: wheels_)
    {
        sCar += "WG: " + wheel.toString() + "\n";
    }

    return sCar;
}

bool Car::isVertexSettable(const b2Vec2 &vertex) const
{
    if( (vertex.Length() < 0.1) || (vertex.Length() > BodyGene::MAX_LENGTH) )
        return false;

    for(const auto& b: body_)
    {
        float32 angle = AngleCalculation()(b.getVertex(), vertex);
        if( abs(angle) < 0.5 )
            return false;
    }
    return true;
}
