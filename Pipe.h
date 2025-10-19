#pragma once
#include <SFML\Graphics.hpp>

class Pipe {
	protected:
		sf::RectangleShape shape;
		float speed;
	public:
		Pipe (const float width, const float height);
		~Pipe ();

		void move ();
		void setPos (float x, float y);
		void draw (sf::RenderWindow& window);
		float getPositionX () const;
		float getPositionY () const;
		float getHeight () const;
		sf::FloatRect getRect () const;
};