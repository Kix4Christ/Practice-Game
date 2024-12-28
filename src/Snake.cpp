#include "Snake.h"
#include "SFML/Graphics.hpp"

enum Direction
{
	up, right, down, left
};



Snake::Snake()
{
	head.dir = right;
	head.position = sf::Vector2i{ 0,0 };
}

Snake::~Snake()
{

}

void Snake::move(Direction dir)
{
	segment newSegment;
	newSegment.position = head.position + dirToVector(dir);
	newSegment.dir = dir;
	segments.push_back(newSegment);
}

sf::Vector2i dirToVector(Direction dir)
{
	if (dir == up) return sf::Vector2i{ 0,1 };
	if (dir == down) return sf::Vector2i{ 0,-1 };
	if (dir == right) return sf::Vector2i{ 1,0 };
	if (dir == left) return sf::Vector2i{ -1,0 };
}

Direction reverseDir(Direction dir)
{
	if (dir == up) return down;
	if (dir == down) return up;
	if (dir == right) return left;
	if (dir == left) return right;
}


