#include "car.h"
#include "simulation/element/element.h"
#include "simulation/element/wheel.h"
#include "simulation/element/polygon.h"
#include "utilfunctions.h"

#include <iostream>
#include <utility>

using namespace std;
using Color = Qt::GlobalColor;

Car::Car(b2Vec2 position): score_(0), timeAlive_(0)
{
    bodyColor_ = static_cast<Color>(Color::darkBlue);
    wheelColor_ = static_cast<Color>(Color::darkRed);
    initLength_ = randLength();

    startPosition_ = position;

    //TODO Move this to private function;
    b2Vec2 prevVertex(0, 0);
    prevVertex += b2Vec2(initLength_, 0);
    int restAngle = 360;
    while(restAngle >= 1)
    {
        int minAngle = 15;
        int angle = minAngle + std::rand() % (180 - minAngle);

        float32 length = randLength();

        Element::Parameters param = Element::Parameters::createRandom();
        if(angle >= restAngle)
        {
            body_.push_back(BodyGene(param, b2Vec2(initLength_, 0)));
            break;
        }

        restAngle -= angle;

        b2Vec2 vertex = VertexCalculation()(prevVertex, angle, length);
        prevVertex = vertex;
        body_.push_back(BodyGene(param, vertex));
    }

    int prevIndex = -1;
    for(int i = 1; i <= 2; ++i)
    {
        Element::Parameters param = Element::Parameters::createRandom();
        int max = WheelGene::MAX_RADIUS;
        int min = 1;
        float32 radius = (double)std::rand() / RAND_MAX;;
        radius *= (max - min);
        radius += min;
        int vertexNumber = std::rand() % body_.size();
        while(vertexNumber == prevIndex)
            vertexNumber = std::rand() % body_.size();
        wheels_.push_back(WheelGene(radius, vertexNumber, param));
    }
}

Car::Car(const Car &other):
    Object(), score_(0), timeAlive_(0), startPosition_(other.startPosition_),
    initLength_(other.initLength_), wheelColor_(other.wheelColor_),
    bodyColor_(other.bodyColor_)
{
    copyGenes(other);
}

Car::Car(const Car &other, bool resetScore):
    Object(other), score_(0), timeAlive_(0), startPosition_(other.startPosition_),
    initLength_(other.initLength_), wheelColor_(other.wheelColor_),
    bodyColor_(other.bodyColor_)
{
    copyGenes(other);
    if(!resetScore)
    {
        score_ = other.score_;
        timeAlive_ = other.timeAlive_;
    }
}

Car::Car(const Car &other, const WheelGene &gene, size_t geneIndex):
    Car(other)
{
    if(geneIndex >= other.wheels_.size())
        throw "Out of body";

    WheelGene wheel(gene, body_.size());
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
    initLength_(first.initLength_), wheelColor_(first.wheelColor_),
    bodyColor_(first.bodyColor_)
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

Car::Car(const Car &first, const Car &second):
    Car(first)
{
    int i = 0;
    wheels_.clear();
    for(const auto &wheel: second.wheels_)
    {
        WheelGene gene(wheel, body_.size());
        wheels_.push_back(gene);
        ++i;
    }
}

QRectF Car::boundingRect() const
{
    return QRectF(-20, -20, 45, 45);
}

bool Car::isCrashed() const
{
    for(Wheels::const_iterator it = wheels_.begin();
        it != wheels_.end(); ++it)
    {
        Wheels::const_iterator it2 = it;
        ++it2;
        for(; it2 != wheels_.end(); ++it2)
        {
            if((*it).getVertexNumber() == (*it2).getVertexNumber())
            {
                return true;
            }
        }
    }

    return false;
}

void Car::initialize()
{
    Object::initialize();
}

void Car::copyGenes(const Car &other)
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

void Car::initialize(std::vector<ElementPtr>& elements)
{
    b2Vec2 vertex;
    vertex.x = initLength_;
    vertex.y = 0;
    // Create car's body
    elements.push_back(ElementPtr(new Polygon(b2Vec2(0, 0),
                                              b2_dynamicBody,
                                              bodyColor_)));

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
        elements.push_back(w.create(vertex, wheelColor_));
    }

    for(auto & e: elements)
    {
        e->collide(false);
    }
}

void Car::createJoints(std::vector<ElementPtr> &elements,
                       b2World& world)
{
    b2RevoluteJointDef jointDef;
    b2Vec2 vertex;

    //Create first joint -- for test
    vertex = body_[wheels_[0].getVertexNumber()].getVertex();
    vertex = vertex;
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
    b2RevoluteJointDef jointDef2;
    vertex = body_[wheels_[1].getVertexNumber()].getVertex();
    vertex = vertex;
    jointDef2.Initialize(elements[2]->getBody(), elements[0]->getBody(), vertex);
    world.CreateJoint(&jointDef2);
    elements_[1]->getBody()->SetAngularVelocity(-20);
    elements_[2]->getBody()->SetAngularVelocity(-20);

    setPosition(startPosition_);
    setPos(getPosition().x, getPosition().y);
    // /////////////
}

bool Car::isMoved(double interval) const
{
    return getPosition().x > startPosition_.x + interval*240;
}

size_t Car::bodySize() const
{
    return body_.size();
}

void Car::updateObject(double interval)
{
    timeAlive_ += interval;
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

bool Car::canBeCreated() const
{
    b2Vec2 initVertex(initLength_, 0);
    const b2Vec2 *prevVertex = &initVertex;
    for(const auto &b: body_)
    {
        b2Vec2 vertex = b.getVertex();
        if(vertex.y == 0)
            vertex.y -= 0.1;
        float32 angle = AngleCalculation()(vertex, *prevVertex);
        if( abs(angle) > 179 )
            return false;
        prevVertex = &(b.getVertex());
    }

    return true;
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

bool Car::operator>=(const Car &rhs)
{
    return !operator< (rhs);
}

bool Car::operator<=(const Car &rhs)
{
    return !operator> (rhs);
}

bool Car::operator>(const Car &rhs)
{
    return score_ > rhs.score_;
}

bool Car::operator<(const Car &rhs)
{
    return score_ < rhs.score_;
}

bool Car::operator!=(const Car &rhs)
{
    return !operator==(rhs);
}

bool Car::operator==(const Car &rhs)
{
    return score_ == rhs.score_;
}
