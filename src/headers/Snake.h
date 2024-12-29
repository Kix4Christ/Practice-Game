#pragma once
#include <SFML/Graphics.hpp>
#include <queue>

#include "Direction.h"

class Playfield;

class Snake
{
	

private:

	class Segment
	{

	private:
		sf::Sprite sprite;
		Playfield& playfield;
	public:
		sf::Vector2i position;

		// absolute direction going towards the head of the snake.
		Direction dir;


		Segment(Playfield& p, sf::Vector2i pos, Direction dir);
		

		void draw(sf::RenderWindow& window, float updateProgress, sf::Vector2i* previousSegment);
		

	};

	Segment* head;
	std::queue<Segment> segments;
	
	int length;

	Playfield* playfield;


	bool canMove(sf::Vector2i pos);

public:
	Snake(Playfield* field);
	~Snake();
	bool move(Direction dir);
	void increaseLength();
	std::string toString();
	void draw(sf::RenderWindow& window, float updateProgress);
};