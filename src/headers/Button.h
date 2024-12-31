#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"


// T is the type of the owner of this button. (or, the type that contains the definition for its onclick)
template <typename T>
class Button
{
private:
	enum ButtonState
	{
		normal,
		hovered,
		pressed
	};

	static const sf::Time hoverFade;
	static const sf::Time clickFade; 

	static const sf::Color normalColor;
	static const sf::Color hoveredColor;
	static const sf::Color pressedColor;

	// ui members.
	sf::RectangleShape* background;
	sf::Text* buttonLabel;

	// state managment
	ButtonState previousState;
	ButtonState state;
	sf::Time timeInState;

	// templated function pointer
	void(T::* onClick)();
	T& caller;

public:
	Button(T& caller, sf::FloatRect bounds, std::string label);
	~Button();
	void update(sf::RenderWindow& window, sf::Time delta);
	void setOnClick(void(T::* onClick)());


private:
	ButtonState getState(sf::RenderWindow& window);
	sf::Color getColor();
	bool mouseOverButton(sf::RenderWindow& window);
	sf::Color getStateColor(ButtonState state);

	// doesn't really belong here, but nowhere else for it to go at present...
	sf::Color lerp(sf::Color a, sf::Color b, float target);

};

#include "../Button.ipp"