#include <SFML/Graphics.hpp>
#include "headers/Resources.h"


Resources* Resources::instance = nullptr;


Resources::Resources()
{
	if (instance != nullptr)
	{
		throw("Resources is a singleton. It may not have multiple instances.");
	}
	
	instance = this;

	// actually initialize.
	arial = sf::Font("arialbd.ttf");
	fruit = sf::Texture("fruit.png");
	fruit.setSmooth(true);
	snakeBend = sf::Texture("snakeBend.png");
	snakeBend.setSmooth(true);
	snakeEnd = sf::Texture("snakeEnd.png");
	snakeEnd.setSmooth(true);
	snakeStraight = sf::Texture("snakeStraight.png");
	snakeStraight.setSmooth(true);
	snakeHead = sf::Texture("snakeHead.png");
	snakeHead.setSmooth(true);
}

Resources::~Resources() {}

Resources& Resources::get()
{
	if (Resources::instance == nullptr)
	{
		new Resources();
	}

	return *Resources::instance;
}

void Resources::destroy()
{
	if (Resources::instance == nullptr)
	{
		return;
	}

	delete Resources::instance;
	Resources::instance = nullptr;
}

