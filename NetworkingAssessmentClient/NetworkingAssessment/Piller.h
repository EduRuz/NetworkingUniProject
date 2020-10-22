#pragma once
#include "GameSprite.h"
class Piller :
	public GameSprite
{
public:
	Piller();
	~Piller();

	void initialize(float xPos, float yPos);

private:

	sf::Texture pillerTexture;
};

