#pragma once
#include <SFML/Graphics.hpp>

class Bird {
	private:
		sf::CircleShape shape;
		float velocity;
		const float gravity = 0.5f;
		const float jumpPower = -6.5f;
		
	public:
		bool status = true; // true = alive
		Bird (float x, float y, float radius = 20.f);
		~Bird ();

		void handleInput (const unsigned int& screen_width);
		void update ();
		void draw (sf::RenderWindow& window);
		void reset(float x, float y, float radius = 45.f);
		sf::FloatRect getRect () const;
};
