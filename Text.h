#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Text {
	private:
		sf::Text text; 
		sf::Color default_color = sf::Color::White;
	public: 
		Text (); // <-- 
		Text (const std::string& txt, sf::Font& font, float x, float y, int size);
		~Text ();

		void draw (sf::RenderWindow& window);
		void setPos (float x, float y);
		void updateText (const std::string* txt);
		void changeColor (const sf::Color& color);
		void changeColor (
			const unsigned int& r, 
			const unsigned int& g, 
			const unsigned int& b
		);
		void setUp (const std::string& txt, sf::Font& font, float x, float y, int size);
};