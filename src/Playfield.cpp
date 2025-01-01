#include <SFML/Graphics.hpp>
#include "headers/Playfield.h"
#include "headers/Snake.h"
#include "headers/Resources.h"
#include <iostream>

Playfield::Playfield(sf::Rect<float> bounds, sf::Vector2i tileSize) : fruitSprite(sf::Sprite(Resources::get().test))
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

	std::srand(std::time(0)); // Seed with current time
	int x = std::rand() % tileSize.x;
	int y = std::rand() % tileSize.y;
	fruitPosition = sf::Vector2i::Vector2(x, y);

}

Playfield::~Playfield() 
{
	delete snake;
}

PlayfieldEvent Playfield::update(Direction playerMove)
{
	
	snake->update(playerMove);

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
	

	drawApple(window, fruitPosition);
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

void Playfield::drawApple(sf::RenderWindow& window, sf::Vector2i position)
{
	//draw an apple
	sf::Texture texture = Resources::get().fruit;
	fruitSprite = sf::Sprite(texture);
	fruitSprite.setOrigin(static_cast<sf::Vector2f>(texture.getSize() / 2u));
	fruitSprite.setPosition(TileToGlobalCoords(position) + (getSizeOfTile() / 2.0f));
	sf::Vector2u texSize = fruitSprite.getTexture().getSize();
	sf::Vector2f tileSize = getSizeOfTile();
	fruitSprite.setScale(sf::Vector2f(tileSize.x / texSize.x, tileSize.y / texSize.y) * 1.05f);

	window.draw(fruitSprite);
}
