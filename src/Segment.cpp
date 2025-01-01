#include <SFML/Graphics.hpp>
#include "headers/Segment.h"
#include "headers/Resources.h"
#include <iostream>

Segment::Segment(Playfield& playfield, sf::Vector2i coords, Segment* towardsTail)
	: sprite(sf::Sprite(Resources::get().test)), playfield(playfield)
{
	// initialize data
	tileCoords = coords;
	this->towardsTail = towardsTail;
	this->towardsHead = nullptr;
	if (towardsTail != nullptr)
	{
		towardsTail->onTowardsHeadAdd(this);
	}

	
	setupSprite(Resources::get().snakeEnd);

	if (towardsTail == nullptr) return;

	
	sprite.setRotation(sf::degrees(180) - Dir::dirToAngle(backward()));
}

Segment::~Segment()
{
	if (towardsTail != nullptr)
	{
		// you aren't supposed to do this?

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

Direction Segment::forward()
{
	
	return Dir::vectorToDir(towardsHead->tileCoords - tileCoords);
}

Direction Segment::backward()
{
	return Dir::vectorToDir(towardsTail->tileCoords-tileCoords);
}

void Segment::onTowardsHeadAdd(Segment* towardsHead)
{
	this->towardsHead = towardsHead;

	if (towardsTail == nullptr)
	{
		setupSprite(Resources::get().snakeEnd);
		sprite.setRotation(sf::degrees(180) - Dir::dirToAngle(forward()));
		return;
	}

	//std::cout << Dir::dirToString(forward()) << Dir::dirToString(backward()) << std::endl;
	if (forward() == Dir::reverseDir(backward()))
	{
		setupSprite(Resources::get().snakeStraight);
		sprite.setRotation(sf::degrees(180) - Dir::dirToAngle(forward()));
		return;
	}

	if (Dir::clockwise(backward()) == forward())
	{
		setupSprite(Resources::get().snakeBend);
		sprite.setRotation(sf::degrees(180) - Dir::dirToAngle(forward()));
		return;
	}

	// surely these shouldn't be the same...
	// can't really test it yet though...
	setupSprite(Resources::get().snakeBend);
	sprite.setRotation(sf::degrees(270) - Dir::dirToAngle(forward()));

	
}

void Segment::onTowardsTailRemoved()
{
	this->towardsTail = nullptr;

	setupSprite(Resources::get().snakeEnd);	
	
	sprite.setRotation(sf::degrees(180)-Dir::dirToAngle(forward()));
}

void Segment::setupSprite(sf::Texture& texture)
{
	sprite = sf::Sprite(texture);
	sprite.setOrigin(static_cast<sf::Vector2f>(texture.getSize() / 2u));
	sprite.setPosition(playfield.TileToGlobalCoords(tileCoords)+(playfield.getSizeOfTile()/2.0f));
	sf::Vector2u texSize = sprite.getTexture().getSize();
	sf::Vector2f tileSize = playfield.getSizeOfTile();
	sprite.setScale(sf::Vector2f(tileSize.x / texSize.x, tileSize.y / texSize.y)*1.05f);

}
