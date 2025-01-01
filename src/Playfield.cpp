#include <SFML/Graphics.hpp>
#include "headers/Playfield.h"
#include "headers/Snake.h"
#include <iostream>

Playfield::Playfield(sf::Rect<float> bounds, sf::Vector2i tileSize)
{
	this->pixelBounds = bounds;
	this->tileSize = tileSize;
	counter = 0;

	// initialize the drawable field
	sf::Vector2f sizeOfTile = getSizeOfTile();
	sf::Color color1(150, 200, 100);
	sf::Color color2(200, 250, 150);

	drawableField = std::vector<std::vector<sf::RectangleShape>>();
	drawableField.reserve(tileSize.x);

	for (int x = 0; x < tileSize.x; x++)
	{
		drawableField.push_back(std::vector<sf::RectangleShape>());
		drawableField[x].reserve(tileSize.y);
		
		for (int y = 0; y < tileSize.y; y++)
		{
			// each rectangle...
			drawableField[x].push_back(sf::RectangleShape(sizeOfTile));
			sf::RectangleShape& rect = drawableField[x][y];
			rect.setFillColor((x + y) % 2 == 1 ? color1 : color2);
			rect.setPosition(TileToGlobalCoords(sf::Vector2i(x, y)));

		}
	}

	// initialize the snake
	snake = new Snake(this);
	for (int i = 0; i < 10; i++)
	{
		snake->increaseLength();
	}
	for (int i = 0; i < 5; i++)
	{
		snake->move(Direction::right);
	}
	for (int i = 0; i < 5; i++)
	{
		snake->move(Direction::down);
	}

}

Playfield::~Playfield() 
{
	delete snake;
}

PlayfieldEvent Playfield::update(Direction playerMove)
{
	// We're just playing right now. move the snake in a circle.
	
	// ignoring the player's desires for now
	/*Direction d = Direction::none;
	switch (counter / 5)
	{
	case 0:
		d = Direction::left;
		break;
	case 1:
		d = Direction::up;
		break;
	case 2:
		d = Direction::right;
		break;
	case 3:
		d = Direction::down;
		break;
	}*/

	snake->move(playerMove);

	counter++;
	counter = counter > 19? counter - 20 : counter;

	return PlayfieldEvent::None;
}

void Playfield::draw(sf::RenderWindow& window, float updateProgress)
{
	
	for (int x = 0; x < tileSize.x; x++)
	{
		for (int y = 0; y < tileSize.y; y++)
		{
			
			window.draw(drawableField[x][y]);
		}
	}

	snake->draw(window, updateProgress);


}

sf::Vector2f Playfield::getSizeOfTile()
{

	return sf::Vector2f(
		(pixelBounds.size.x / (float)(tileSize.x)),
		(pixelBounds.size.y / (float)(tileSize.y))
	);
}

sf::Vector2f Playfield::TileToGlobalCoords(sf::Vector2i tileCoords)
{
	sf::Vector2f sizeOfTile = getSizeOfTile();
	sf::Vector2f relCoords = sf::Vector2f(tileCoords.x * sizeOfTile.x, tileCoords.y * sizeOfTile.y);
	return relCoords + pixelBounds.position;
}

sf::Rect<int> Playfield::getInflatedTileBounds()
{
	return sf::Rect<int>(sf::Vector2i(-1, -1), tileSize+sf::Vector2i(1,1));
}

sf::Vector2i Playfield::getSizeInTiles()
{
	return tileSize;
}
