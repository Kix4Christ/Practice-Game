#include <SFML/Graphics.hpp>
#include <sstream>
#include <queue>

#include "headers/Snake.h"
#include "headers/Direction.h"
#include "headers/Playfield.h"


Snake::Snake(Playfield *field) : playfield(field)
{
	head.dir = Direction::right;
	head.position = sf::Vector2i{ 0,0 };
	segments.push(head);
	length = 1;

}

Snake::~Snake()
{

}

void Snake::increaseLength() { length++; }



bool Snake::move(Direction dir)
{
	//if the the direction is backwards or none, just keep it going forwards
	if (Dir::reverseDir(dir) == head.dir || dir == Direction::none) dir = head.dir;

	Segment newSegment;
	newSegment.position = head.position + Dir::dirToVector(dir);
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


bool Snake::canMove(sf::Vector2i pos)
{
	std::queue<Segment> copy = segments;

	//if it is colliding with any previous segment
	while (!copy.empty())
	{
		if (copy.front().position == pos) return false;
		copy.pop();
	}
	//if it is in bounds
	if (pos.x < 0 || pos.y < 0) return false;
	
	if (!playfield->getInflatedTileBounds().contains(pos)) return false;

	return true;
}


std::string Snake::toString()
{
	std::stringstream stream;
	stream << "length: " << length << "\n";
	std::queue<Segment> copy = segments;

	int i = 0;
	while (!copy.empty()) 
	{
		Segment s = copy.front();
		copy.pop();
		stream << "segment " << i << " pos: " << s.position.x << " " << s.position.y << " dir: " << s.dir << "\n";
		i++;
	}

	return stream.str();
}

void Snake::draw(sf::RenderWindow& window, float updateProgress)
{
}

void Snake::Segment::draw(sf::RenderWindow& window, float updateProgress, sf::Vector2i previousSegment)
{
}
