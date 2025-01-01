#include "headers/DirectionalInput.h"

DirectionalInput::DirectionalInput()
{
    Direction nextDir = Direction::none;
}

void DirectionalInput::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        nextDir = Direction::up;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        nextDir = Direction::right;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        nextDir = Direction::down;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        nextDir = Direction::left;
    }
    
}

Direction DirectionalInput::getDirection()
{
    return nextDir;
}