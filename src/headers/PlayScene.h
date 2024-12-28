#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"


class PlayScene : public Scene
{
private:
	const sf::Font& textFont;
	sf::Text scoreText;
	

public:
	PlayScene(const sf::Font& font, sf::Window& window);
	Scene* update(sf::RenderWindow& window, sf::Time frameDelta) override;


};