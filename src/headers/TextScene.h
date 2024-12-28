#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"


class TextScene : public Scene
{
private:
	const static int fontSize = 72;
    const sf::Font& titleFont;
	sf::Text titleText;
	bool enterPressed;

public:
	TextScene(const sf::Font& font, std::string title, sf::Window& window);
	Scene* update(sf::RenderWindow& window, sf::Time frameDelta) override;


};