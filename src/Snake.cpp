#include "headers/Snake.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include "headers/Direction.h"
#include <queue>


Snake::Snake()
{
	head.dir = Direction::right;
	head.position = sf::Vector2i{ 0,0 };
	segments.push(head);
	length = 1;
	boardWidth = 5;
	boardHeight = 5;
}

Snake::~Snake()
{

}

void Snake::increaseLength() { length++; }



bool Snake::move(Direction dir)
{
	//if the the direction is backwards or none, just keep it going forwards
	if (reverseDir(dir) == head.dir || dir == Direction::none) dir = head.dir;

	segment newSegment;
	newSegment.position = head.position + dirToVector(dir);
	newSegment.dir = dir;
	//can it move there?
	if(!canMove(newSegment.position)) return false;

	segments.push(newSegment);
	head = newSegment;

	//delete the tail if needed
	if (length < segments.size())
	{
		segments.pop();
	}
	return true;
}

sf::Vector2i Snake::dirToVector(Direction dir)
{
	if (dir == Direction::up) return sf::Vector2i{ 0,-1 };
	if (dir == Direction::down) return sf::Vector2i{ 0,1 };
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

bool Snake::canMove(sf::Vector2i pos)
{
	std::queue<segment> copy = segments;

	//if it is colliding with any previous segment
	while (!copy.empty())
	{
		if (copy.front().position == pos) return false;
		copy.pop();
	}
	//if it is in bounds
	if (pos.x < 0 || pos.y < 0) return false;
	if(pos.x >= boardWidth || pos.y >= boardHeight)
	return true;
}

std::string Snake::toString()
{
	std::stringstream stream;
	stream << "length: " << length << "\n";
	std::queue<segment> copy = segments;

	int i = 0;
	while (!copy.empty()) 
	{
		segment s = copy.front();
		copy.pop();
		stream << "segment " << i << " pos: " << s.position.x << " " << s.position.y << " dir: " << s.dir << "\n";
		i++;
	}

	return stream.str();
}
