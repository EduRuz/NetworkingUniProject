#include "GameSprite.h"


/**
Constructor for GameSprite, inherits from sf::RectangleShape
*/
GameSprite::GameSprite()
{
}


GameSprite::~GameSprite()
{
}

/**
Updates GameSprite variables used for specific animations.
@param float delta time from main game loop for animations.
*/
void GameSprite::update(float deltaTime)
{
	animate(deltaTime);
}

/**
Insert the player information so sprite predicition can work as intended.
@param float X position.
@param float Y position.
@param sf::Int32 the time the X and Y position were retreived at.
*/
void GameSprite::insertPlayerInformation(float xpos, float ypos, sf::Int32 time)
{
	SpriteInformation spInfo;
	spInfo.x = xpos;
	spInfo.y = ypos;
	spInfo.elapsedTime = time;

	if (spriteInfo.size() == 2) {
		spriteInfo.pop_front();
		spriteInfo.push_back(spInfo);
	}
	else {
		spriteInfo.push_back(spInfo);
	}
}

/**
Linear Prediction using the last two locations to guess where the sprite is going.
@param sf::Int32 Current elapsed time.
*/
void GameSprite::spritePrediction(sf::Int32 currentTime)
{

	SpriteInformation pInfo2 = spriteInfo.front();
	SpriteInformation pInfo1 = spriteInfo.back(); //Most recent message

	predictedPosition.x = pInfo1.x;
	predictedPosition.y = pInfo1.y;

	sf::Vector2f velocity;
	sf::Vector2f distBetween;
	sf::Uint32 timeBetween;
	sf::Vector2f predictedDist;

	distBetween.x = pInfo1.x - pInfo2.x;
	distBetween.y = pInfo1.y - pInfo2.y;

	timeBetween = pInfo1.elapsedTime - pInfo2.elapsedTime;

	velocity.x = distBetween.x / timeBetween;
	velocity.y = distBetween.y / timeBetween;

	predictedDist.x = velocity.x * (currentTime - pInfo1.elapsedTime);
	predictedDist.y = velocity.y * (currentTime - pInfo1.elapsedTime);

	predictedPosition.x = pInfo1.x + predictedDist.x;
	predictedPosition.y = pInfo1.y + predictedDist.y;

}

/**
returns the collision box for the sprite.
*/
sf::FloatRect GameSprite::getCollisionBox()
{
	return sf::FloatRect(collisionBox.left + getPosition().x, collisionBox.top + getPosition().y, collisionBox.width, collisionBox.height);
}

/**
Collision responce for sprites.
*/
void GameSprite::collisionResponse(GameSprite * sp)
{

}

/**
	Animation for the child classes.
	@param deltaTime for controlling the animations.
*/
void GameSprite::animate(float deltaTime)
{
	if (isAnimated) {
		currentAnimation->animate(deltaTime);
		setTextureRect(currentAnimation->getCurrentFrame());
	}
}




