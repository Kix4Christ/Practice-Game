#pragma once
#include <SFML/Graphics.hpp>

#include "Scene.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Time elapsedTime;
	Scene* currentScene;



public:
	Game();
	~Game();
private:
	void run();
	void update(sf::Time deltaTime);
};