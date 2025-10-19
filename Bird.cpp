#include "Bird.h"

Bird::Bird (float x, float y, float radius)
    : velocity(0.f)
{
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Cyan);
    shape.setPosition(x, y);
    shape.setOutlineThickness(2.3f);
    shape.setOutlineColor(sf::Color(2, 184, 184));
}

Bird::~Bird () {}

void Bird::handleInput (const unsigned int& screen_height) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        velocity = jumpPower;
    }

    if (shape.getPosition().y >= screen_height + 400) {
        status = false;
    }
    else if (shape.getPosition().y < -200) {
        status = false;
    }
}

void Bird::update () {
    velocity += gravity;
    if (velocity > 15.f)
        velocity = 15.f; // optional clamp

    shape.move(0, velocity);

    if (shape.getPosition().y + shape.getRadius() * 2 > 800) {
        status = false;
    }
}

void Bird::draw (sf::RenderWindow& window) {
    window.draw(shape);
}

void Bird::reset(float x, float y, float radius) {
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Cyan);
    shape.setOutlineThickness(2.3f);
    shape.setOutlineColor(sf::Color(2, 184, 184));
    shape.setPosition(x, y);

    velocity = 0.f;
    status = true;
}

sf::FloatRect Bird::getRect() const {
    return shape.getGlobalBounds();
}
