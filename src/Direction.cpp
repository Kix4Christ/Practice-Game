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
	if (dir == Direction::up) return Direction::down;
	if (dir == Direction::down) return Direction::up;
	if (dir == Direction::right) return Direction::left;
	else return Direction::right;
}