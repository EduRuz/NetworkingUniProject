#pragma once
#include "SFML\Graphics.hpp"
#include "GameSprite.h"
#include "Animation.h"
#include "Input.h"

class PlayerCharacter :
	public GameSprite
{
public:
	PlayerCharacter();
	~PlayerCharacter();

	void initialize(sf::RenderWindow* wind, Input* in, std::string spriteSheetPath, int xPos, int yPos);
	void inputControl(float deltaTime);
	void update(float deltaTime);
	void networkUpdate(float deltaTime);
	void renderPlayerComponents();
	//void animate(float deltaTime);
	void setBounds(int north, int south, int east, int west);
	void onExit();

	int count = 0;
private:

	struct LevelBounds {
		int north;
		int south;
		int east;
		int west;

	};



	void managePlayerHealth();

	LevelBounds levelBounds;
	//int movementSpeed;
	//float xPosition;
	//float yPosition;
	//bool isMoving;
	//Animation* currentAnimation;


	sf::RenderWindow* window;
	Input* input;
	sf::Texture playerSpiteSheet;

	Animation standLookUp;
	Animation standLookDown;
	Animation standLookLeft;
	Animation standLookRight;

	Animation walkUp;
	Animation walkDown;
	Animation walkLeft;
	Animation walkRight;
};

