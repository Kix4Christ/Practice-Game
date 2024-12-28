#include "headers/PlayScene.h"
#include "headers/Playfield.h"

#include <SFML/Graphics.hpp>
#include <sstream>


PlayScene::PlayScene(const sf::Font& font, sf::Window& window)
	: Scene(font), textFont(font), playfield(nullptr)
{
	
	scoreText = new sf::Text(font, "Placeholder", 48u);
	scoreText->setPosition(sf::Vector2f(50, 50));

	// initialize the playfield
	playfield = new Playfield(sf::FloatRect(sf::Vector2f(50, 120), sf::Vector2f(1500, 900-170)), sf::Vector2i(30, 14));
	
	score = 0;
}

PlayScene::~PlayScene()
{
	delete scoreText;
	delete playfield;
}

Scene* PlayScene::update(sf::RenderWindow& window, sf::Time frameDelta)
{
	window.clear(sf::Color(160, 190, 110));

	// draw score
	std::stringstream stream;
	stream << "Score: " << std::fixed << std::setprecision(2) << score;
	scoreText->setString(stream.str());
	window.draw(*scoreText);


	playfield->draw(window, 0);

	Scene::update(window, frameDelta);


	return nullptr;
}
