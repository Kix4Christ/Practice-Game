#include "headers/Snake.h"
#include <SFML/Graphics.hpp>
#include "headers/Direction.h"


Snake::Snake(): head()
{
	head.dir = Direction::right;
	head.position = sf::Vector2i{ 0,0 };
	length = 1;
}

Snake::~Snake()
{

}

void Snake::increaseLength() { length++; }

void Snake::move()
{//if there is no input, move forward
	move(head.dir);
}

void Snake::move(Direction dir)
{
	//if the the direction is backwards, just keep it going forwards
	if (reverseDir(dir) == head.dir) dir = head.dir;

	segment newSegment;
	newSegment.position = head.position + dirToVector(dir);
	newSegment.dir = dir;
	segments.push_back(newSegment);
	head = newSegment;
}

sf::Vector2i Snake::dirToVector(Direction dir)
{
	if (dir == Direction::up) return sf::Vector2i{ 0,1 };
	if (dir == Direction::down) return sf::Vector2i{ 0,-1 };
	if (dir == Direction::right) return sf::Vector2i{ 1,0 };
	else return sf::Vector2i{ -1,0 };
}

Direction Snake::reverseDir(Direction dir)
{
	if (dir == Direction::up) return Direction::down;
	if (dir == Direction::down) return Direction::up;
	if (dir == Direction::right) return Direction::left;
	else return Direction::right;
}


