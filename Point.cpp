#include "Point.h"

Point::Point(const float width, const float height)
	: Pipe(width, height) {
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(sf::Color(255, 255, 255, 0));
}
Point::~Point() {};