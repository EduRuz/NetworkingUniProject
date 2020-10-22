#include "Boss.h"


/**
Constructor for Boss, inherits from gameSprite as a sf::RectangleShape
*/
Boss::Boss()
{
}


Boss::~Boss()
{
}

/**
Initializes variables and classes from the Boss class to use.
@param sf::RenderWindow* pointer to the window for drawing to.
*/
void Boss::initialize(sf::RenderWindow* wind)
{
	window = wind;

	dragonTexture.loadFromFile("Gfx/Ice Dragon.png");
	setTexture(&dragonTexture);
	setSize(sf::Vector2f(200,200));
	//setPosition(1000, 900);
	xPosition = 1000;
	yPosition = 50;
	movementSpeed = 50.0;
	movingUp = false;
	isAnimated = false;
	isMoving = true;

	healthValue = 14;
	healthBar.setFillColor(sf::Color::Blue);
	healthBar.setSize(sf::Vector2f(200, 10));

	healthBarBackground.setFillColor(sf::Color::Black);
	healthBarBackground.setSize(sf::Vector2f(200, 10));

}

void Boss::update(float deltaTime)
{
	//setPosition(xPosition, yPosition);
	//move(deltaTime);
	manageBossHealth();
	
}

void Boss::renderBossComponents()
{
	window->draw(healthBarBackground);
	window->draw(healthBar);
}

void Boss::move(float deltaTime)
{
	if (yPosition <= 50) {
		movingUp = false;
	}
	
	if (yPosition >= 700) {
		movingUp = true;
	}

	if (movingUp) {
		yPosition -= (movementSpeed * deltaTime);
	}
	else {
		yPosition += (movementSpeed * deltaTime);
	}
}

void Boss::manageBossHealth()
{
	healthBarSize = healthValue * 8;
	healthBar.setSize(sf::Vector2f(healthBarSize, 10));
	healthBar.setPosition(getPosition().x, getPosition().y - 15.0f);

	healthBarBackground.setPosition(getPosition().x, getPosition().y - 15.0f);
}
