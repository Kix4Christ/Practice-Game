#include <SFML/Graphics.hpp>
#include <sstream>
#include <queue>

#include "headers/Snake.h"
#include "headers/Direction.h"
#include "headers/Playfield.h"
#include "headers/Resources.h"
#include <iostream>


Snake::Snake(Playfield *field) 
	: playfield(field)
{
	// make the first segment
	sf::Vector2i pos = playfield->getSizeInTiles() / 2;
	head = new Segment(*playfield, pos, nullptr);
	tail = head;
	length = 1;
	pendingLength = 1;

	if (!move(Direction::right))
	{
		throw std::logic_error("Playfield too small to initialize snake.");
	}

	nextMove = Direction::right;
	
}

Snake::~Snake()
{
	// we need to delete our segments.
	while (tail != nullptr)
	{
		removeTail();
	}
}

void Snake::increaseLength(int by) 
{
	pendingLength+=by;
}



std::string Snake::toString()
{
	std::stringstream stream;
	stream << "length: " << length << "\nPending: "<< pendingLength <<"\nStarting from Head:\n";

	int i = 0;
	for (Segment* seg = head; seg != nullptr; seg = seg->nextTowardsTail())
	{
		stream << "segment #" << i << "@ (" << seg->getTileCoords().x << ", "<< seg->getTileCoords().y << ")\n";
		i++;
	}

	return stream.str();
}

bool Snake::update(Direction moveNext)
{
	if (!move(nextMove)) return false;
	nextMove = moveNext;
	return true;	
}

void Snake::draw(sf::RenderWindow& window, float updateProgress)
{
	for (Segment* seg = head; seg != nullptr; seg = seg->nextTowardsTail())
	{
		seg->draw(window, updateProgress);
	}

}

bool Snake::contains(sf::Vector2i pos)
{
	for (Segment* seg = head; seg != nullptr; seg = seg->nextTowardsTail())
	{
		if (seg->getTileCoords() == pos) return true;
	}
	return false;
}

// returns the direction in front of the snake's head.
Direction Snake::forwards()
{
	if (head == tail) return Direction::right;
	return Dir::reverseDir(head->backward());

}

void Snake::removeTail()
{
	Segment* newTail = tail->nextTowardsHead();
	length--;
	delete tail;
	tail = newTail;
}


bool Snake::move(Direction dir)
{


	//if the the direction is backwards or none, just keep it going forwards
	if (Dir::reverseDir(dir) == forwards() || dir == Direction::none)
	{
		dir = forwards();
	}

	sf::Vector2i newSegmentPos = head->getTileCoords() + Dir::dirToVector(dir);

	// can we perform the movement?
	if (!canMove(newSegmentPos)) return false;


	// add a new segment
	head = new Segment(*playfield, newSegmentPos, head);
	length++;

	//delete the tail if needed
	if (pendingLength==0)
	{
		removeTail();
		return true;
	}
	
	pendingLength--;
	return true;

}


bool Snake::canMove(sf::Vector2i pos)
{
	// well, that cleaned up super nicely.
	if (contains(pos)) return false;
	if (pos.x < 0 || pos.y < 0) return false;
	return playfield->getInflatedTileBounds().contains(pos);
	
}

