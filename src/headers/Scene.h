#pragma once
#include <SFML/Graphics.hpp>
#include <deque>

/*
* A scene represents a single screen or menu.
Scenes manage input for the game. 

*/
class Scene
{
private:
	class FrameHistory
	{

	private:
		sf::Time& lastFrameDelta;
		std::deque<sf::Time>* frameDeltas;
		float framerate;
		

	public:
		FrameHistory();
		FrameHistory(const FrameHistory& other);
		FrameHistory& operator= (const FrameHistory& other);
		~FrameHistory();
		void update(sf::Time frameDelta);
		float getFramerate();
	};

private:
	FrameHistory history;
	sf::Text* fpsText;
protected:
	Scene* next;

public:
	//Scene(const Scene& previous);
	Scene();
	~Scene();
	virtual Scene* update(sf::RenderWindow& window, sf::Time frameDelta);


	

};




