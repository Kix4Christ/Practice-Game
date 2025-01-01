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

	snake->increaseLength(7);
	
	for (int i = 0; i < 2; i++)
	{
		snake->update(Direction::right);
	}
	for (int i = 0; i < 4; i++)
	{
		snake->update(Direction::down);
	}

}

Playfield::~Playfield() 
{
	delete snake;
}

PlayfieldEvent Playfield::update(Direction playerMove)
{
	
	snake->update(playerMove);

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
