#include <SFML/Graphics.hpp>
#include "headers/Scene.h"
#include "headers/MenuScene.h"
#include "headers/PlayScene.h"
#include "headers/Resources.h"


MenuScene::MenuScene(std::string title, std::string subtitle, std::string buttonTitle, sf::Window& window) : Scene(),
	titleText(sf::Text(Resources::get().arial)), 
	subTitle(sf::Text(Resources::get().arial))
{
	enterPressed = false;

	titleText.setString(title);
	titleText.setCharacterSize(fontSize);
	titleText.setPosition(sf::Vector2f(
		(window.getSize().x - titleText.getGlobalBounds().size.x) / 2.0f,
		180.0f
	));

	subTitle.setString(subtitle);
	subTitle.setCharacterSize(smallFontSize);
	subTitle.setPosition(sf::Vector2f(
		(window.getSize().x - subTitle.getGlobalBounds().size.x) / 2.0f,
		320.0f
	));


	

	button = new Button<MenuScene>
	(
		*this,
		sf::FloatRect(
			sf::Vector2f(window.getSize().x/4.0f, 450), 
			sf::Vector2f(window.getSize().x/2.0f, 200)
		),
		buttonTitle
	);
	button->setOnClick(&MenuScene::nextScene);
}

MenuScene::~MenuScene()
{
	delete button;
}

Scene* MenuScene::update(sf::RenderWindow& window, sf::Time frameDelta)
{
	window.clear(sf::Color(160, 190, 110));
	window.draw(titleText);
	window.draw(subTitle);

	Scene* toReturn = nullptr;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{
		enterPressed = true;
	}
	else
	{
		if (enterPressed)
		{
			next = new PlayScene(window);
		}
	}

	button->update(window, frameDelta);

	return Scene::update(window, frameDelta);
	
}

void MenuScene::nextScene()
{
	// this is a massive hack, try to ignore until SCENE NEEDS WINDOW REFERENCE AS MEMBER
	enterPressed = true;
	// next = new PlayScene(window);
}
