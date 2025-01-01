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