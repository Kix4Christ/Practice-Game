#include <SFML/Graphics.hpp>

#include "headers/Scene.h"
#include <sstream>
#include "headers/Resources.h"



Scene::FrameHistory::FrameHistory()  : lastFrameDelta(sf::milliseconds(0))
{
    frameDeltas = new std::deque<sf::Time>();

    framerate = 0.0f;
}


Scene::FrameHistory::~FrameHistory()
{
    delete frameDeltas;
}

// rolling average of last second of frames.
void Scene::FrameHistory::update(sf::Time delta)
{
    // the number of samples we keep is prortional to the framerate,
    // so we take a rolling average of effectively the last second.
    int64_t rollingSize = (static_cast<int>(framerate));
    if (rollingSize < 5) rollingSize = 5;


    // update the queue
    frameDeltas->push_back(delta);
    while (frameDeltas->size() > rollingSize)
    {
        frameDeltas->pop_front();
    }

    // calculate the rolling average now
    sf::Time averageDelta = sf::Time::Zero;

    // the limit is the lesser of the rolling average size and the size of the deque. (when the # of samples is growing)
    int64_t samples = frameDeltas->size();

    for (int i = 0; i < samples; i++)
    {
        averageDelta += (*frameDeltas)[i];
    }
    averageDelta /= samples;

    framerate = 1 / averageDelta.asSeconds();
}

float Scene::FrameHistory::getFramerate()
{
    return framerate;
}

Scene::Scene()
{
    fpsText = new sf::Text(Resources::get().arial);
    fpsText->setPosition(sf::Vector2f(10, 10));
    next = nullptr;

}

Scene::~Scene()
{
    delete fpsText;
}

Scene* Scene::update(sf::RenderWindow& window, sf::Time frameDelta)
{
    history.update(frameDelta);

    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << history.getFramerate()<< " FPS";
    fpsText->setString(stream.str());
    window.draw(*fpsText);


    return next;

}
