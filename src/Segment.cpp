#include <SFML/Graphics.hpp>
#include "headers/Segment.h"
#include "headers/Resources.h"

Segment::Segment(Playfield& playfield, sf::Vector2i coords, Segment* towardsTail)
	: sprite(sf::Sprite(Resources::get().test))
{
	// initialize data
	tileCoords = coords;
	this->towardsTail = towardsTail;
	this->towardsHead = nullptr;
	if (towardsTail != nullptr)
	{
		towardsTail->onTowardsHeadAdd(this);
	}

	// iniitalize sprite
	sprite.setPosition(playfield.TileToGlobalCoords(tileCoords));
	sf::Vector2u texSize = sprite.getTexture().getSize();
	sf::Vector2f tileSize = playfield.getSizeOfTile();
	sprite.setScale(sf::Vector2f(tileSize.x / texSize.x, tileSize.y / texSize.y));
}

Segment::~Segment()
{
	if (towardsTail != nullptr)
	{
		throw std::logic_error("Only tail Segment of Snake may be deleted.");
	}
	towardsHead->onTowardsTailRemoved();
}

Segment* Segment::nextTowardsHead()
{
	return towardsHead;
}

Segment* Segment::nextTowardsTail()
{
	return towardsTail;
}

sf::Vector2i Segment::getTileCoords()
{
	return tileCoords;
}

void Segment::draw(sf::RenderWindow& window, float updateProgress)
{

	// draw the sprite.
	window.draw(sprite);
}

void Segment::onTowardsHeadAdd(Segment* towardsHead)
{
	this->towardsHead = towardsHead;
	
}

void Segment::onTowardsTailRemoved()
{
	this->towardsTail = nullptr;
}
