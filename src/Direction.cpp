#include <SFML/Graphics.hpp>
#include "headers/Direction.h"

sf::Vector2i Dir::dirToVector(Direction dir)
{
	if (dir == Direction::up) return sf::Vector2i{ 0,-1 };
	if (dir == Direction::down) return sf::Vector2i{ 0,1 };
	if (dir == Direction::right) return sf::Vector2i{ 1,0 };
	else return sf::Vector2i{ -1,0 };
}

Direction Dir::reverseDir(Direction dir)
{
	if (dir == Direction::none) return Direction::none;
	if (dir == Direction::up) return Direction::down;
	if (dir == Direction::down) return Direction::up;
	if (dir == Direction::right) return Direction::left;
	else return Direction::right;
}

bool Dir::isReverse(Direction a, Direction b)
{
	return reverseDir(a) == b;
}


// none is neither vertical nor horizontal.

bool Dir::isVertical(Direction dir)
{
	return dir == Direction::up || dir == Direction::down;
}

bool Dir::isHorizontal(Direction dir)
{
	return dir == Direction::left || dir == Direction::right;
}
