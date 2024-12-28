#pragma once
#include <SFML/Graphics.hpp>
#include "Direction.h"
#include <queue>

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

	std::queue<segment> segments;
	
	int length;
	int boardWidth;
	int boardHeight;

	sf::Vector2i dirToVector(Direction dir);
	Direction reverseDir(Direction dir);
	bool canMove(sf::Vector2i pos);

public:
	Snake();
	~Snake();
	bool move(Direction dir);
	void increaseLength();
	std::string toString();
};