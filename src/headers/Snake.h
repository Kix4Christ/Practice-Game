#pragma once
#include <SFML/Graphics.hpp>
#include <deque>

#include "Direction.h"

class Playfield;

class Snake
{
	

private:

	class Segment
	{

	private:
		// absolute direction going towards the head of the snake.
		Direction dir;

		sf::Sprite sprite;
		Playfield& playfield;
	public:
		sf::Vector2i position;

		
		/*
		Dir is the absolute direction facing towards the head segment.
		prev is the absolute dir facing towards the head segment of the previous segment.
		*/
		Segment(Playfield& p, sf::Vector2i pos, Direction dir, Direction prev);
		void draw(sf::RenderWindow& window, float updateProgress, sf::Vector2i* previousSegment);
		void setDir(Direction d, Direction previousSegmentDirection);
		Direction getDir();
		

	};

	Segment* head;

	// the tail is at the front, the head is at the back.
	std::deque<Segment> segments;
	
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