#include <SFML/Graphics.hpp>
#include "headers/Direction.h"

sf::Vector2i Dir::dirToVector(Direction dir)
{
	if (dir == Direction::up) return sf::Vector2i{ 0,-1 };
	if (dir == Direction::down) return sf::Vector2i{ 0,1 };
	if (dir == Direction::right) return sf::Vector2i{ 1,0 };
	if (dir == Direction::left) return sf::Vector2i{ -1,0 };
	return sf::Vector2i(0, 0);
}

Direction Dir::vectorToDir(sf::Vector2i vect)
{
	if (vect == sf::Vector2i(-1, 0)) return Direction::left;
	if (vect == sf::Vector2i(1, 0))	 return Direction::right;
	if (vect == sf::Vector2i(0, -1)) return Direction::up;
	if (vect == sf::Vector2i(0, 1))	 return Direction::down;
	return Direction::none;

	
}

Direction Dir::reverseDir(Direction dir)
{
	if (dir == Direction::up) return Direction::down;
	if (dir == Direction::down) return Direction::up;
	if (dir == Direction::right) return Direction::left;
	else return Direction::right;
}

sf::Angle Dir::dirToAngle(Direction dir)
{
	int deg = 0;
	switch (dir)
	{
	case right:
		deg = 0;
		break;
	case up:
		deg = 90;
		break;
	case left:
		deg = 180;
		break;
	case down:
		deg = 270;
		break;
	}
	return sf::degrees(deg);
}

std::string Dir::dirToString(Direction dir)
{
	switch (dir)
	{
	case right:
		return "right";
	case up:
		return "up";
	case left:
		return "left";
	case down:
		return "down";
		
	}

	return "none";
}

Direction Dir::clockwise(Direction dir)
{

	switch (dir)
	{
	case right:
		return Direction::down;
	case up:
		return Direction::right;
	case left:
		return Direction::up;
	case down:
		return Direction::left;

	}

	return Direction::none;
	
}
