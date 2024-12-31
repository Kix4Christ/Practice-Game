#pragma once

template <typename T>
const sf::Color Button<T>::normalColor = sf::Color(100, 200, 100);

template <typename T>
const sf::Color Button<T>::hoveredColor = sf::Color(150, 220, 150);

template <typename T>
const sf::Color Button<T>::pressedColor = sf::Color(80, 170, 80);

template <typename T>
const sf::Time Button<T>::hoverFade = sf::milliseconds(350);
template <typename T>
const sf::Time Button<T>::clickFade = sf::milliseconds(200);


template <typename T>
Button<T>::Button(T& caller, sf::FloatRect bounds, std::string label) : caller(caller)
{
	background = new sf::RectangleShape(bounds.size);
	background->setPosition(bounds.position);
	background->setFillColor(normalColor);
	background->setOutlineThickness(8);
	background->setOutlineColor(sf::Color::White);

	buttonLabel = new sf::Text(Resources::get().arial, label, 48u);
	// figure out the position of the buttonLabel...
	buttonLabel->setOrigin(buttonLabel->getLocalBounds().getCenter());
	buttonLabel->setPosition(bounds.getCenter());
	buttonLabel->setFillColor(sf::Color::White);


	previousState = ButtonState::hovered;
	state = ButtonState::normal;
	onClick = nullptr;
	timeInState = hoverFade; // to prevent the button from transitioning colors for no reason.
}


template <typename T>
Button<T>::~Button()
{
	delete background;
	delete buttonLabel;
}


template <typename T>
void Button<T>::update(sf::RenderWindow& window, sf::Time delta)
{
	ButtonState prev = state;
	state = getState(window); // onClick may be called here.
	if (prev != state)
	{
		previousState = prev;
		timeInState = delta;
	}
	else
	{
		timeInState += delta;
	}

	background->setFillColor(getColor());

	// draw the gorsh dang button
	// that feels like a treavor comment to me. Am I crazy?
	window.draw(*background);
	window.draw(*buttonLabel);
}


template <typename T>
void Button<T>::setOnClick(void(T::* onClick)())
{
	this->onClick = onClick;
}

// Called once per update. May call button's onclick.
// due to magic witchcraft reasons, the keyword typename is required.
template <typename T>
typename Button<T>::ButtonState Button<T>::getState(sf::RenderWindow& window)
{
	switch (state)
	{
	case ButtonState::normal:
		// a button can transition from the normal state to either the 
		// hovered or pressed state when the mouse is over it.

		if (mouseOverButton(window))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) return ButtonState::pressed;
			return ButtonState::hovered;
		}

		return ButtonState::normal;

	case ButtonState::hovered:
		// a hovered button can become normal if the mouse leaves the button, or become pressed if the mouse button is pressed.
		if (!mouseOverButton(window)) return ButtonState::normal;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) return ButtonState::pressed;
		return ButtonState::hovered;

	case ButtonState::pressed:
		// A pressed button can only transition to another state when the mouse button is released.
		// if it is released when the mouse is over the button, the button is hovered, and the button's onclick is called.
		// if not, the button will be in the normal state, and no action is taken.

		// This allows the user to 'cancel' a button press by dragging the mouse away from the button before releasing, which is 
		// how most buttons work across most UI's.

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) return ButtonState::pressed;
		if (mouseOverButton(window))			
		{
			// calling the onclick function is very funky.
			if (onClick != nullptr) (caller.*onClick)();
			return ButtonState::hovered;
		}

		return ButtonState::normal;

	}

	return ButtonState::normal;
}

template <typename T>
sf::Color Button<T>::getColor()
{

	// figure out which time value we need. Pressed > Hovered > Normal;
	sf::Time targetTime;
	if (previousState == ButtonState::pressed || state == ButtonState::pressed)
	{
		// yeah, making states a struct or something might've been helpful.
		// but hey, I'm not writing a UI framework, am I, I'm writing a single button class.
		targetTime = clickFade;
	}
	else
	{
		targetTime = hoverFade;
	}

	if (timeInState >= targetTime)
	{
		return(getStateColor(state));
	}

	return lerp(getStateColor(previousState), getStateColor(state), timeInState / targetTime);


}

template <typename T>
bool Button<T>::mouseOverButton(sf::RenderWindow& window)
{
	return  background->getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
}

//constexpr?
template <typename T>
sf::Color Button<T>::getStateColor(ButtonState state)
{
	// you know, it occurs to me that maybe having state as a struct or something would be better...
	switch (state)
	{
	case ButtonState::normal:
		return normalColor;
	case ButtonState::hovered:
		return hoveredColor;
	case ButtonState::pressed:
		return pressedColor;
	}
	return normalColor;
}

// lineraly interpolate through rgb space between two colors.
template <typename T>
sf::Color Button<T>::lerp(sf::Color a, sf::Color b, float target)
{

	uint8_t red = (a.r * (1 - target)) + (b.r * target);
	uint8_t green = (a.g * (1 - target)) + (b.g * target);
	uint8_t blue = (a.b * (1 - target)) + (b.b * target);

	return sf::Color(red, green, blue);
}


