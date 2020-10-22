#pragma once
#include "SFML\Graphics.hpp"
#include "GameSprite.h"

class Boss :
	public GameSprite
{
public:
	Boss();
	~Boss();

	void initialize(sf::RenderWindow* wind);
	void update(float deltaTime);
	void renderBossComponents();

private:

	void move(float deltaTime);
	void manageBossHealth();

	sf::RenderWindow* window;

	bool movingUp;

	sf::Texture dragonTexture;
};

