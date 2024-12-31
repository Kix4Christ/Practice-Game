#include "headers/PlayScene.h"
#include "headers/Playfield.h"

#include <SFML/Graphics.hpp>
#include <sstream>
#include "headers/Resources.h"


PlayScene::PlayScene(sf::Window& window)
	: Scene(), playfield(nullptr)
{
	
	scoreText = new sf::Text(Resources::get().arial, "Placeholder", 48u);
	scoreText->setPosition(sf::Vector2f(50, 50));

	// initialize the playfield
	playfield = new Playfield(sf::FloatRect(sf::Vector2f(50, 120), sf::Vector2f(1500, 900-170)), sf::Vector2i(30, 14));
	
	score = 0;
	timeSinceTick = sf::Time::Zero;
	tickLength = sf::seconds(0.5);
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

	//see if a simulation update is needed
	timeSinceTick += frameDelta;
	if (timeSinceTick >= tickLength)
	{
		timeSinceTick -= tickLength;//carry over
		updateSimulation();
	}

	playfield->draw(window, 0);

	Scene::update(window, frameDelta);

	return nullptr;
}

void PlayScene::updateSimulation()
{
	//get input
	//move snake
	playfield->update(Direction::none);
}
