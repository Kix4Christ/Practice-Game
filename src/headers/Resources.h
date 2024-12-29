#pragma once
#include <SFML/Graphics.hpp>

// singletons are gross, but these kinda make sense.
class Resources
{
private:
	static Resources* instance;
public:
	sf::Font arial;
	sf::Texture fruit;
	sf::Texture snakeBend;
	sf::Texture snakeEnd;
	sf::Texture snakeStraight;


private:
	Resources();
	~Resources();

public:
	static Resources& get();
	static void destroy();





};



