#include <SFML/Graphics.hpp>
#include "headers/Playfield.h"

Playfield::Playfield(sf::Rect<float> bounds, sf::Vector2i tileSize)
{
	this->pixelBounds = bounds;
	this->tileSize = tileSize;
}

Playfield::~Playfield() {}

PlayfieldEvent Playfield::update(Direction playerMove)
{
	return PlayfieldEvent::None;
}

void Playfield::draw(sf::RenderWindow& window, float updateProgress)
{

	sf::Color color1(150, 200, 100);
	sf::Color color2(200, 250, 150);

	sf::RectangleShape rect(getSizeOfTile());

	for (int x = 0; x < tileSize.x; x++)
	{
		for (int y = 0; y < tileSize.y; y++)
		{
			rect.setFillColor( (x + y) % 2 == 1 ? color1 : color2);
			rect.setPosition(TileToGlobalCoords(sf::Vector2i(x, y)));
			window.draw(rect);
		}
	}


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
