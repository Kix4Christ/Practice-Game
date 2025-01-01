#pragma once
#include <SFML/Graphics.hpp>
#include "Playfield.h"

// represents a segment of a snake.
class Segment
{
private:
	sf::Vector2i tileCoords;
	sf::Sprite sprite;

	// a segment does not own its pointers!
	Segment* towardsHead;
	Segment* towardsTail;

	Playfield& playfield;

public:
	// segments are created at the head of a snake, so only a tail reference is needed.
	Segment(Playfield& playfield, sf::Vector2i coords, Segment* towardsTail);
	~Segment();

	Segment* nextTowardsHead();
	Segment* nextTowardsTail();
	sf::Vector2i getTileCoords();

	// update is a value from 0 to 1, representing the progress through an interval between simulation updates.
	void draw(sf::RenderWindow& window, float updateProgress);

	Direction forward();
	Direction backward();

private:
	// called on a segment when a new head is created.
	void onTowardsHeadAdd(Segment* towardsHead);

	// called on a segment when the adjacent tail is removed, making them the tail.
	void onTowardsTailRemoved();

	void setupSprite(sf::Texture &texture);
	
};