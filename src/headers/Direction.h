#pragma once
#include <SFML/Graphics.hpp>

enum Direction
{
	up, right, down, left, none
};


class Dir
{
public:
	static sf::Vector2i dirToVector(Direction dir);

	static Direction vectorToDir(sf::Vector2i dir);

	static Direction reverseDir(Direction dir);

	// where right is 0 degrees and counterclockwise is positive.
	static sf::Angle dirToAngle(Direction dir);

	static std::string dirToString(Direction dir);

	static Direction clockwise(Direction dir);


};