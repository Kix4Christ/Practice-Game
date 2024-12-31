#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Button.h"


class TextScene : public Scene
{
private:
	const static int fontSize = 100;
   
	sf::Text titleText;
	Button<TextScene>* button;
	bool enterPressed;

public:
	TextScene(std::string title, std::string button, sf::Window& window);
	~TextScene();
	Scene* update(sf::RenderWindow& window, sf::Time frameDelta) override;

private:
	void nextScene();


};