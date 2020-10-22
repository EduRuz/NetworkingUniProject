#include "Piller.h"



Piller::Piller()
{
}


Piller::~Piller()
{
}

/**
Initializes Piller variables.
@param float X position of the Sprite.
@param float Y position of the Sprite;
*/
void Piller::initialize(float xPos, float yPos)
{
	pillerTexture.loadFromFile("Gfx/Piller.png");
	setTexture(&pillerTexture);
	setSize(sf::Vector2f(50, 100));
	setPosition(xPos, yPos);


	isAnimated = false;
	isMoving = true;
}
