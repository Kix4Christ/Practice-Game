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

	static bool isReverse(Direction a, Direction b);
	
	static bool isVertical(Direction dir);

	static bool isHorizontal(Direction dir);


};