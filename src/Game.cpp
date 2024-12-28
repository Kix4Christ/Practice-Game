#include <SFML/Graphics.hpp>
#include "headers/Game.h"
#include "headers/Scene.h"
#include "headers/TextScene.h"

Game::Game()
{
    sf::Font arial("arialbd.ttf");
    
    clock = sf::Clock();
    elapsedTime = sf::Time::Zero;
    window = sf::RenderWindow(sf::VideoMode({ 1600u, 900u }), "Snake Test");
    currentScene = new TextScene(arial, "Snake Test", window);
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
