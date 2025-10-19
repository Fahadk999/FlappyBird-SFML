#include "Text.h"

Text::Text () {}; // <-- delete if unused
Text::Text (const std::string& txt, sf::Font& font, float x, float y, int size) {
		setUp(txt, font, x, y, size);
}
Text::~Text () {}

void Text::draw(sf::RenderWindow& window) {
	window.draw(text);
}

void Text::setPos(float x, float y) {
	text.setPosition(sf::Vector2f(x,y));
}

void Text::updateText(const std::string* txt) {
	text.setString(*txt);
}

void Text::changeColor (const sf::Color& color) {
	text.setFillColor(color);
}
void Text::changeColor (
	const unsigned int& r,
	const unsigned int& g,
	const unsigned int& b
) {
	text.setFillColor(sf::Color(r, g, b));
}

void Text::setUp (const std::string& txt, sf::Font& font, float x, float y, int size) {
	text.setFont(font);
	text.setString(txt);
	text.setCharacterSize(size);
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f(x,y));
}