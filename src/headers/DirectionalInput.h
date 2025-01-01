#pragma once
#include <SFML/Graphics.hpp>
#include "Direction.h"

class DirectionalInput
{
private:
	Direction nextDir;
public:
	DirectionalInput();
	void update();
	Direction getDirection();
};