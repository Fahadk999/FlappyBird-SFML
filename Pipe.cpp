#include "Pipe.h"

Pipe::Pipe (const float width, const float height) 
	: speed(10.f) 
{
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(sf::Color(3, 252, 82));
}
Pipe::~Pipe () {}

void Pipe::move () {
	shape.move(-speed, 0);
}

void Pipe::setPos (float x, float y) {
	shape.setPosition(sf::Vector2f(x, y));
}

void Pipe::draw (sf::RenderWindow& window) {
	window.draw(shape);
}

float Pipe::getPositionX () const {
	return shape.getPosition().x;
}

float Pipe::getPositionY () const {
	return shape.getPosition().y;
}

float Pipe::getHeight () const {
	return shape.getSize().y;
}

sf::FloatRect Pipe::getRect () const {
	return shape.getGlobalBounds();
}