#pragma once

enum Direction
{
	up, right, down, left, none
};


class Dir
{
public:
	static sf::Vector2i dirToVector(Direction dir);

	static Direction reverseDir(Direction dir);


};