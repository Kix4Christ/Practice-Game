#pragma once
#include <SFML/Graphics.hpp>
#include "Direction.h"

enum PlayfieldEvent
{
	None,
	playerAte,
	playerDied,

};

class Playfield
{
private:
	 sf::Rect<float> pixelBounds;

	 // size in tiles of the playfield
	 sf::Vector2i tileSize;

public:
	Playfield(sf::Rect<float> bounds, sf::Vector2i tileSize);
	~Playfield();

	PlayfieldEvent update(Direction playerMove);
	void draw(sf::RenderWindow& window, float updateProgress);

	sf::Vector2f getSizeOfTile();
	sf::Vector2f TileToGlobalCoords(sf::Vector2i tileCoords);
};