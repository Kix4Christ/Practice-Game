#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Playfield.h"

/*
* For all intents and purposes, this is the main file of the snake game.
*/
class PlayScene : public Scene
{
private:
	const sf::Font& textFont;
	sf::Text* scoreText;
	Playfield* playfield;
	unsigned int score;

	sf::Time timeSinceTick;
	sf::Time tickLength;
	

public:
	PlayScene(const sf::Font& font, sf::Window& window);
	~PlayScene();
	Scene* update(sf::RenderWindow& window, sf::Time frameDelta) override;

private:
	void updateSimulation();

};