#pragma once
#include <SFML/Graphics.hpp>
#include "Direction.h"

class Snake;

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

	 // VERY TEMPORARY!!!
	 int counter; 

	 // size in tiles of the playfield
	 sf::Vector2i tileSize;

	 std::vector<std::vector<sf::RectangleShape>> drawableField;	
	 Snake* snake;

public:
	Playfield(sf::Rect<float> bounds, sf::Vector2i tileSize);
	~Playfield();

	PlayfieldEvent update(Direction playerMove);
	void draw(sf::RenderWindow& window, float updateProgress);

	sf::Vector2f getSizeOfTile();
	sf::Vector2f TileToGlobalCoords(sf::Vector2i tileCoords);
	
	sf::Rect<int> getInflatedTileBounds();
	sf::Vector2i getSizeInTiles();
};