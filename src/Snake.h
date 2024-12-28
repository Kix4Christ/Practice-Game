#pragma once
#include <SFML/Graphics.hpp>
#include "Direction.h"

class Snake
{
private:
	struct segment
	{
		sf::Vector2i position;
		Direction dir;

		segment()
		{
			position = sf::Vector2i{ 0,0 };
			dir = Direction::right;
		}
	}head;

	std::vector<segment> segments;
	
	int length;

	sf::Vector2i dirToVector(Direction dir);
	Direction reverseDir(Direction dir);

public:
	Snake();
	~Snake();
	void move();
	void move(Direction dir);
	void increaseLength();
};