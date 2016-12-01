#include "element.h"
#include <iostream>
#include <utility>
#include "utilfunctions.h"
#define DEGTORAD 0.0174532925199432957f

using namespace std;

Element::Element(const b2Vec2& position, const b2BodyType& bodyType,
                 const Qt::GlobalColor& color)
    //parameters_({0,0,0})
{
    //body
    bodyDef_.type = bodyType;
    bodyDef_.position = position;
    color_ = color;
}

Element::Element(const Element &other): body_(nullptr), bodyDef_(other.bodyDef_),
    color_(other.color_)
{
    for(const auto &f: other.fixtureDefs_)
    {
        b2BlockAllocator allocator;
        b2FixtureDef fixture;
        fixture.shape = ShapeCloning()(f.shape);
        fixture.userData = f.userData;
        fixture.friction = f.friction;
        fixture.restitution = f.restitution;
        fixture.density = f.density;
        fixture.isSensor = f.isSensor;
        fixture.filter = f.filter;
        addFixture(fixture);
    }
}

Element::~Element()
{
    for(auto &f : fixtureDefs_)
    {
       delete f.shape;
    }
}

void Element::draw(QPainter &painter) const
{
    painter.setPen(QPen(color_,0.2));

    for(b2Fixture* f = body_->GetFixtureList(); f; f = f->GetNext())
    {
        this->drawElement(painter, body_->GetPosition(),
                          body_->GetAngle(), f->GetShape());
    }
}

void Element::create(b2World &world)
{
    body_ = world.CreateBody(&bodyDef_);
    body_->SetUserData(this);
    body_->SetFixedRotation(false);
    for(const auto& fixtureDef: fixtureDefs_)
    {
        body_->CreateFixture(&fixtureDef);
    }
}

void Element::destroy(b2World &world)
{
    world.DestroyBody(body_);
}

void Element::addFixture(const b2FixtureDef& fixtureDef)
{
    fixtureDefs_.push_back(fixtureDef);
}

void Element::addFixture(b2Shape *shape, const Parameters& parameters)
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
    fixtureDef.density = parameters.density;
    fixtureDef.friction = parameters.friction;
    fixtureDef.restitution = parameters.restitution;

    addFixture(fixtureDef);
}

void Element::collide(bool c)
{
    if(c == true)
        for(auto &f: fixtureDefs_)
            f.filter.groupIndex = -4;
    else
        for(auto &f: fixtureDefs_)
            f.filter.groupIndex = 0;
}

void Element::addFixture(b2Shape *shape)
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;

    addFixture(fixtureDef);
}

b2Body* Element::getBody()
{
    return body_;
}

const b2Shape *Element::getShape()
{
    return fixtureDefs_[0].shape;
}

void Element::swap(Element &other)
{
    std::swap(body_, other.body_);
    std::swap(bodyDef_, other.bodyDef_);
    std::swap(color_, other.color_);
    fixtureDefs_.swap(other.fixtureDefs_);
}

Element::Parameters Element::Parameters::createRandom()
{
    float32 density = std::rand() % Element::Parameters::MAX_DENSITY;
    int maxFriction = Element::Parameters::MAX_FRICTION * 100;
    float32 friction = static_cast<float32>(1 + std::rand() % maxFriction) / maxFriction;
    int maxRestitution = Element::Parameters::MAX_RESTITUTION * 100;
    float32 restitution = static_cast<float32>(std::rand() % maxRestitution) / maxRestitution;

    return Parameters(density, friction, restitution);
}

std::__cxx11::string Element::Parameters::toString() const
{
    std::string sParameters;
    sParameters += std::to_string(density) + " ";
    sParameters += std::to_string(friction) + " ";
    sParameters += std::to_string(restitution);

    return sParameters;
}

const int Element::Parameters::MAX_DENSITY = 100;
const double Element::Parameters::MAX_FRICTION = 1;
const double Element::Parameters::MAX_RESTITUTION = 1;
