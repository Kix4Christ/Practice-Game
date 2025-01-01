#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Button.h"


class MenuScene : public Scene
{
private:
	const static int fontSize = 100;
   
	sf::Text titleText;
	Button<MenuScene>* button;
	bool enterPressed;

public:
	MenuScene(std::string title, std::string button, sf::Window& window);
	~MenuScene();
	Scene* update(sf::RenderWindow& window, sf::Time frameDelta) override;

private:
	void nextScene();


};