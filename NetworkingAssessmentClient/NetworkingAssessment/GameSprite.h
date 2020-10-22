#pragma once
#include "SFML\Graphics.hpp"
#include "Animation.h"
#include "Input.h"
#include <list>

enum DIRECTION { UP, DOWN, LEFT, RIGHT };

class GameSprite :
	public sf::RectangleShape
{
public:
	GameSprite();
	~GameSprite();

	struct PlayerInformation {

		int playerID;
		float x, y;
		sf::Int32 elapsedTime;
		int type = 1;

	};


	struct BossInformation {

		float bossX, bossY;
		float fireX, fireY;
		int type = 0;

	};

	struct SpriteInformation {

		float x, y;
		sf::Int32 elapsedTime;

	};

	void update(float deltaTime);
	void setHealthValue(int value) { healthValue = value; };

	//for sprite collision
	bool isCollider() { return collider; };
	void setCollider(bool b) { collider = b; };

	void insertPlayerInformation(float xpos, float ypos, sf::Int32 time);
	void spritePrediction(sf::Int32 currentTime);
	sf::Vector2f getSpritePrediction() { return predictedPosition; };

	sf::FloatRect getCollisionBox();
	void setCollisionBox(float x, float y, float width, float height) { collisionBox = sf::FloatRect(x, y, width, height);};
	void setCollisionBox(sf::FloatRect fr) { collisionBox = fr; };
	virtual void collisionResponse(GameSprite* sp);

protected:



	void animate(float deltaTime);
	void reduceHealth() { healthValue--; };
	
	std::list<SpriteInformation> spriteInfo;

	float xPosition;
	float yPosition;
	float movementSpeed;
	bool isMoving = false;
	DIRECTION dir;

	Animation* currentAnimation;
	bool isAnimated = false;

	sf::RectangleShape healthBar;
	sf::RectangleShape healthBarBackground;
	int healthValue;
	float healthBarSize;

	//Collision vars
	sf::FloatRect collisionBox;
	bool collider;

	sf::Vector2f predictedPosition;


};

