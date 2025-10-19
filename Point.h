#pragma once
#include <SFML/Graphics.hpp>
#include "Pipe.h"

class Point : public Pipe {
	public:
		bool scored = false;

		Point (const float width, const float height);
		~Point ();
};