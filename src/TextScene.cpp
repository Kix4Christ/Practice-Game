#include <SFML/Graphics.hpp>
#include "headers/Scene.h"
#include "headers/TextScene.h"
#include "headers/PlayScene.h"

TextScene::TextScene(const sf::Font& font, std::string title, sf::Window& window)
	: Scene(font), titleFont(font), titleText(sf::Text(font, title, fontSize))
{
	enterPressed = false;
	titleText.setPosition(sf::Vector2f(
		(window.getSize().x - titleText.getGlobalBounds().size.x) / 2.0f,
		50.0f
	));

}

Scene* TextScene::update(sf::RenderWindow& window, sf::Time frameDelta)
{
	window.clear(sf::Color(150, 200, 100));
	window.draw(titleText);

	Scene* toReturn = nullptr;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{
		enterPressed = true;
	}
	else
	{
		if (enterPressed)
		{
			toReturn = new PlayScene(titleFont, window);
		}
	}

	Scene::update(window, frameDelta);
	return toReturn;
}
