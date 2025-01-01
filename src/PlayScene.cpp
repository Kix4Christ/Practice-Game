#include "headers/PlayScene.h"
#include "headers/Playfield.h"

#include <SFML/Graphics.hpp>
#include <sstream>
#include "headers/Resources.h"
#include "headers/DirectionalInput.h"
#include "headers/MenuScene.h"


PlayScene::PlayScene(sf::Window& window)
	: Scene(), playfield(nullptr)
{
	
	scoreText = new sf::Text(Resources::get().arial, "Placeholder", 48u);
	scoreText->setPosition(sf::Vector2f(50, 50));

	// initialize the playfield
	playfield = new Playfield(sf::FloatRect(sf::Vector2f(50, 120), sf::Vector2f(1500, 900-170)), sf::Vector2i(15, 7));
	
	score = 0;
	timeSinceTick = sf::Time::Zero;
	tickLength = sf::seconds(0.5);

	directionalInput = DirectionalInput();
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
		updateSimulation(window);
	}

	playfield->draw(window, 0);

	directionalInput.update();

	Scene::update(window, frameDelta);

	return next;
}

void PlayScene::updateSimulation(sf::RenderWindow& window)
{
	//get input
	Direction dir = directionalInput.getDirection();
	//move snake
	PlayfieldEvent e = playfield->update(dir);
	if (e == PlayfieldEvent::playerAte)
	{
		score++;
		int ms = 500 - (score * 5);
		if (ms < 100) ms = 100;
		tickLength = sf::milliseconds(ms);
	}

	if (e == PlayfieldEvent::playerDied)
	{
		next = new MenuScene("You Lost!", "Score: " + std::to_string(score), "Try Again", window);
	}
	
}
