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

	segments.push(Segment(*field, playfield->getSizeInTiles() / 2, Direction::right));
	head = &segments.back();
	length = 1;

}

Snake::~Snake()
{

}

void Snake::increaseLength() { length++; }



bool Snake::move(Direction dir)
{
	//if the the direction is backwards or none, just keep it going forwards
	if (Dir::reverseDir(dir) == head->dir || dir == Direction::none) dir = head->dir;

	Segment newSegment(*playfield, head->position + Dir::dirToVector(dir), dir);

	//can it move there?
	if(!canMove(newSegment.position)) return false;

	segments.push(newSegment);
	head = &segments.back();

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
	std::queue<Segment> copy = segments;

	//if it is colliding with any previous segment
	sf::Vector2i* lastPos = nullptr;
	while (!copy.empty())
	{
		
		Segment& seg = copy.front();
		copy.pop();
		seg.draw(window, updateProgress, lastPos);
		lastPos = &seg.position; // this uses & as an address, not reference.
								// or maybe it is a reference in C++ land? I guess it would make sense if a
								// reference could be implicitly cast to a pointer or something
		
	}

}

Snake::Segment::Segment(Playfield& p, sf::Vector2i pos, Direction dir): playfield(p), sprite(sf::Sprite(Resources::get().test))
{
	position = pos;
	this->dir = dir;
	sprite.setPosition(playfield.TileToGlobalCoords(position));
	sf::Vector2u texSize = sprite.getTexture().getSize();
	sf::Vector2f tileSize = playfield.getSizeOfTile();
	sprite.setScale(sf::Vector2f(tileSize.x / texSize.x, tileSize.y / texSize.y));

}

void Snake::Segment::draw(sf::RenderWindow& window, float updateProgress, sf::Vector2i* previousSegment)
{
	window.draw(sprite);
}
