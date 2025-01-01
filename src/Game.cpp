#include <SFML/Graphics.hpp>
#include "headers/Game.h"
#include "headers/Scene.h"
#include "headers/MenuScene.h"
#include "headers/Resources.h"

Game::Game()
{
  
    
    clock = sf::Clock();
    elapsedTime = sf::Time::Zero;
    window = sf::RenderWindow(sf::VideoMode({ 1600u, 900u }), "Snake Test");
    currentScene = new MenuScene("Snake Test", "Play game", window);
    run();

}

Game::~Game()
{
    delete currentScene;
}




void Game::run()
{
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        sf::Time t = clock.getElapsedTime();
        sf::Time deltaTime = t - elapsedTime;
        elapsedTime = clock.getElapsedTime();

        update(deltaTime);
    }

}

void Game::update(sf::Time deltaTime)
{
    window.clear();
    Scene* newScene = currentScene->update(window, deltaTime);
    if (newScene != nullptr)
    {
        delete currentScene;
        currentScene = newScene;
    }


    window.display();
}
