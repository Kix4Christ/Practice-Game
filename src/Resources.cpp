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
	snakeBend = sf::Texture("snakeBend.png");
	snakeEnd = sf::Texture("snakeEnd.png");
	snakeStraight = sf::Texture("snakeStraight.png");
	test = sf::Texture("test.png");
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

