#include <SFML/Graphics.hpp>
#include <sstream>
#include <queue>

#include "headers/Snake.h"
#include "headers/Direction.h"
#include "headers/Playfield.h"
#include "headers/Resources.h"


Snake::Snake(Playfield *field) 
	: playfield(field)
{

	segments.push_back(Segment(*field, playfield->getSizeInTiles() / 2, Direction::right, Direction::none));
	head = &segments.back();
	length = 1;// probably should change to 2.

}

Snake::~Snake()
{

}

void Snake::increaseLength() { length++; }



bool Snake::move(Direction dir)
{
	//if the the direction is backwards or none, just keep it going forwards
	if (Dir::reverseDir(dir) == head->getDir() || dir == Direction::none) dir = head->getDir();

	Segment newSegment(*playfield, head->position + Dir::dirToVector(dir), Direction::none, head->getDir());

	
	//can it move there?
	if(!canMove(newSegment.position)) return false;

	// Tell the old head what direction we're traveling.
	Direction behindOldHead = segments.size() < 2 ? Direction::none : segments[segments.size() - 2].getDir();
	head->setDir(dir, behindOldHead); // the old head needs to point towards the new head.

	// add the new head
	segments.push_back(newSegment);
	head = &segments.back();

	//delete the tail if needed
	if (length < segments.size())
	{
		segments.pop_front();
	}
	return true;
}


bool Snake::canMove(sf::Vector2i pos)
{
	// now that this is a deque we could just iterate through it normally, but it's not broken so eh.
	std::deque<Segment> copy = segments;

	//if it is colliding with any previous segment
	while (!copy.empty())
	{
		if (copy.front().position == pos) return false;
		copy.pop_front();
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
	std::deque<Segment> copy = segments;

	int i = 0;
	while (!copy.empty()) 
	{
		Segment s = copy.front();
		copy.pop_front();
		stream << "segment " << i << " pos: " << s.position.x << " " << s.position.y << " dir: " << s.getDir() << "\n";
		i++;
	}

	return stream.str();
}

void Snake::draw(sf::RenderWindow& window, float updateProgress)
{
	std::deque<Segment> copy = segments;

	//if it is colliding with any previous segment
	sf::Vector2i* lastPos = nullptr;
	while (!copy.empty())
	{
		
		Segment& seg = copy.front();
		copy.pop_front();
		seg.draw(window, updateProgress, lastPos);
		lastPos = &seg.position; // this uses & as an address, not reference.
								// or maybe it is a reference in C++ land? I guess it would make sense if a
								// reference could be implicitly cast to a pointer or something
		
	}

}

Snake::Segment::Segment(Playfield& p, sf::Vector2i pos, Direction dir, Direction prev): playfield(p), sprite(sf::Sprite(Resources::get().snakeStraight))
{
	position = pos;
	setDir(dir, prev);
	


	
	sf::Vector2u texSize = sprite.getTexture().getSize();
	sf::Vector2f tileSize = playfield.getSizeOfTile();
	sprite.setScale(sf::Vector2f(tileSize.x / texSize.x, tileSize.y / texSize.y));
	sprite.setOrigin(static_cast<sf::Vector2f>(texSize / 2u));
	sprite.setPosition(playfield.TileToGlobalCoords(position)+(playfield.getSizeOfTile()/2.0f));

}

void Snake::Segment::draw(sf::RenderWindow& window, float updateProgress, sf::Vector2i* previousSegment)
{
	if (previousSegment == nullptr)
	{
		sprite.setTexture(Resources::get().snakeEnd);
	}
	window.draw(sprite);
}

void Snake::Segment::setDir(Direction d, Direction previousSegmentDirection)
{
	dir = d;
	Direction prev = previousSegmentDirection;

	sprite.setRotation(sf::Angle::Zero);
	// this is to catch both the head and tail, since one of theirs will be none.
	


	if (dir == Direction::none || prev == Direction::none)
	{
		sprite.setTexture(Resources::get().snakeEnd);

		Direction capDir = dir;
		float degrees = 0;
		if (capDir == Direction::none)
		{
			capDir = prev;
			degrees += 180;
		}

		if (capDir == Direction::up)
		{
			degrees += 90;
		}

		if (capDir == Direction::right)
		{
			degrees += 180;
		}

		if (capDir == Direction::down)
		{
			degrees += 270;
		}

		sprite.setRotation(sf::degrees(degrees));

		return;
	}

	if (dir != prev)
	{
		sprite.setTexture(Resources::get().snakeBend);

		// more code here to determine rotation.

		return;
	}

	sprite.setTexture(Resources::get().snakeStraight);
	if (Dir::isVertical(dir))
	{
		sprite.setRotation(sf::degrees(90));
	}

}

Direction Snake::Segment::getDir()
{
	return dir;
}
