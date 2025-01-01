#pragma once
#include <SFML/Graphics.hpp>
#include <queue>

#include "Direction.h"
#include "Segment.h"

class Playfield;



class Snake
{
	

private:

	// a snake owns all of its segments.
	Segment* head;
	Segment* tail;

	int length;
	int pendingLength;

	Direction nextMove;
	Playfield* playfield;
	

public:
	Snake(Playfield* field);
	~Snake();

	void increaseLength(int by);
	std::string toString();

	bool update(Direction moveNext);
	void draw(sf::RenderWindow& window, float updateProgress);

private:
	Direction forwards();
	void removeTail();
	bool move(Direction dir);
	bool canMove(sf::Vector2i pos);

};