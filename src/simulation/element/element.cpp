#include "element.h"
#include <iostream>
#define DEGTORAD 0.0174532925199432957f

Element::Element(const b2Vec2& position, const b2BodyType& bodyType,
                 const Qt::GlobalColor& color)
    //parameters_({0,0,0})
{
    //body
    bodyDef_.type = bodyType;
    bodyDef_.position = position;
    color_ = color;
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
