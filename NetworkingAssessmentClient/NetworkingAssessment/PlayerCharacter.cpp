#include "PlayerCharacter.h"


/**
Constructor for PlayerCharacter, inherits from gameSprite as a sf::RectangleShape
*/
PlayerCharacter::PlayerCharacter()
{
}


PlayerCharacter::~PlayerCharacter()
{
}

/**
Initializes the variables needed for the PlayerCharacter class.
@param sf::RenderWindow* pointer for drawing to.
@param Input* pointer for controlling input.
@param string Path for the spritesheet to be used. *Must be a specific sprite sheet from *
@param int The X position for the sprite.
@param int The Y position for the sprite.
*/
void PlayerCharacter::initialize(sf::RenderWindow* wind, Input * in, std::string spriteSheetPath, int xPos, int yPos)
{
	window = wind;
	input = in;
	playerSpiteSheet.loadFromFile(spriteSheetPath);
	setTexture(&playerSpiteSheet);
	setSize(sf::Vector2f(50, 50));
	xPosition = xPos;
	yPosition = yPos;
	movementSpeed = 6;
	healthValue = 5;
	healthBar.setFillColor(sf::Color::Green);
	healthBar.setSize(sf::Vector2f(50, 10));
	healthBarBackground.setFillColor(sf::Color::Black);
	healthBarBackground.setSize(sf::Vector2f(50, 10));

	standLookUp.addFrame(sf::IntRect(7, 1037, 50, 50));
	standLookUp.addFrame(sf::IntRect(71, 1037, 50, 50));
	standLookUp.setFrameSpeed(0.5f / 0.5f);

	standLookLeft.addFrame(sf::IntRect(7, 845, 50, 50));
	standLookLeft.addFrame(sf::IntRect(71, 845, 50, 50));
	standLookLeft.setFrameSpeed(0.5f / 0.5f);

	standLookDown.addFrame(sf::IntRect(7, 909, 50, 50));
	standLookDown.addFrame(sf::IntRect(71, 909, 50, 50));
	standLookDown.setFrameSpeed(0.5f / 0.5f);

	standLookRight.addFrame(sf::IntRect(7, 974, 50, 50));
	standLookRight.addFrame(sf::IntRect(71, 974, 50, 50));
	standLookRight.setFrameSpeed(0.5f / 0.5f);

	// Setup walk animation.
	walkUp.addFrame(sf::IntRect(7, 523, 50, 50));
	walkUp.addFrame(sf::IntRect(71, 523, 50, 50));
	walkUp.addFrame(sf::IntRect(135, 523, 50, 50));
	walkUp.addFrame(sf::IntRect(199, 523, 50, 50));
	walkUp.addFrame(sf::IntRect(264, 523, 50, 50));
	walkUp.addFrame(sf::IntRect(327, 523, 50, 50));
	walkUp.addFrame(sf::IntRect(391, 523, 50, 50));
	walkUp.addFrame(sf::IntRect(456, 523, 50, 50));
	walkUp.addFrame(sf::IntRect(519, 523, 50, 50));
	walkUp.setFrameSpeed(1.f / 10.f);

	// Setup walk animation.
	walkLeft.addFrame(sf::IntRect(7, 589, 50, 50));
	walkLeft.addFrame(sf::IntRect(71, 589, 50, 50));
	walkLeft.addFrame(sf::IntRect(135, 589, 50, 50));
	walkLeft.addFrame(sf::IntRect(199, 589, 50, 50));
	walkLeft.addFrame(sf::IntRect(264, 589, 50, 50));
	walkLeft.addFrame(sf::IntRect(327, 589, 50, 50));
	walkLeft.addFrame(sf::IntRect(391, 589, 50, 50));
	walkLeft.addFrame(sf::IntRect(456, 589, 50, 50));
	walkLeft.addFrame(sf::IntRect(519, 589, 50, 50));
	walkLeft.setFrameSpeed(1.f / 10.f);

	// Setup walk animation.
	walkDown.addFrame(sf::IntRect(7, 653, 50, 50));
	walkDown.addFrame(sf::IntRect(71, 653, 50, 50));
	walkDown.addFrame(sf::IntRect(135, 653, 50, 50));
	walkDown.addFrame(sf::IntRect(199, 653, 50, 50));
	walkDown.addFrame(sf::IntRect(264, 653, 50, 50));
	walkDown.addFrame(sf::IntRect(327, 653, 50, 50));
	walkDown.addFrame(sf::IntRect(391, 653, 50, 50));
	walkDown.addFrame(sf::IntRect(456, 653, 50, 50));
	walkDown.addFrame(sf::IntRect(519, 653, 50, 50));
	walkDown.setFrameSpeed(1.f / 10.f);

	// Setup walk animation.
	walkRight.addFrame(sf::IntRect(7, 717, 50, 50));
	walkRight.addFrame(sf::IntRect(71, 717, 50, 50));
	walkRight.addFrame(sf::IntRect(135, 717, 50, 50));
	walkRight.addFrame(sf::IntRect(199, 717, 50, 50));
	walkRight.addFrame(sf::IntRect(264, 717, 50, 50));
	walkRight.addFrame(sf::IntRect(327, 717, 50, 50));
	walkRight.addFrame(sf::IntRect(391, 717, 50, 50));
	walkRight.addFrame(sf::IntRect(456, 717, 50, 50));
	walkRight.addFrame(sf::IntRect(519, 717, 50, 50));
	walkRight.setFrameSpeed(1.f / 10.f);

	currentAnimation = &standLookDown;
	setTextureRect(currentAnimation->getCurrentFrame());
	isAnimated = true;
}

/**
Called every frame to control input for the sprite.
@param float Delta time for movement of sprite.
*/
void PlayerCharacter::inputControl(float deltaTime)
{
	if (input->isKeyDown(sf::Keyboard::Left)) {
		currentAnimation = &walkLeft;
		currentAnimation->reset();
		currentAnimation->setLooping(false);
		setTextureRect(currentAnimation->getCurrentFrame());
		xPosition -= movementSpeed;
		animate(deltaTime);
		input->setKeyUp(sf::Keyboard::Left);
	}

	if (input->isKeyDown(sf::Keyboard::Right)) {
		xPosition += movementSpeed;
		currentAnimation = &walkRight;
		currentAnimation->reset();
		currentAnimation->setLooping(false);
		setTextureRect(currentAnimation->getCurrentFrame());
		input->setKeyUp(sf::Keyboard::Right);
	}

	if (input->isKeyDown(sf::Keyboard::Up)) {
		currentAnimation = &walkUp;
		currentAnimation->reset();
		currentAnimation->setLooping(false);
		setTextureRect(currentAnimation->getCurrentFrame());
		yPosition -= movementSpeed;
		input->setKeyUp(sf::Keyboard::Up);
	}

	if (input->isKeyDown(sf::Keyboard::Down)) {
		currentAnimation = &walkDown;
		currentAnimation->reset();
		currentAnimation->setLooping(false);
		setTextureRect(currentAnimation->getCurrentFrame());
		yPosition += movementSpeed;
		input->setKeyUp(sf::Keyboard::Down);
	}

	if (input->isKeyDown(sf::Keyboard::Space)) {
		healthValue--;
		input->setKeyUp(sf::Keyboard::Down);
	}
	
}

/**
Called every frame to update variables for the client side sprite.
@param float delta time from main game loop.
*/
void PlayerCharacter::update(float deltaTime)
{
	setPosition(xPosition, yPosition);
	animate(deltaTime);
	managePlayerHealth();
}

/**
Called every frame to update variables for the network sprite.
@param float delta time from main game loop.
*/
void PlayerCharacter::networkUpdate(float deltaTime)
{
	animate(deltaTime);
	managePlayerHealth();
}

/**
called when needed to show the health bar of the player above the sprite.
*/
void PlayerCharacter::renderPlayerComponents()
{
	window->draw(healthBarBackground);
	window->draw(healthBar);
}

/**
Sets the bounds that the player cannot move past
TODO still to be added.
*/
void PlayerCharacter::setBounds(int north, int south, int east, int west)
{
}

/**
Cleans up pointer variables when game is closed.
*/
void PlayerCharacter::onExit()
{
	delete input;
	input = NULL;

	delete currentAnimation;
	currentAnimation = NULL;
}

/**
Manages player health value and health bar size. Player death is worked out here.
*/
void PlayerCharacter::managePlayerHealth()
{

	switch (healthValue) {
	case 5:
		healthBar.setFillColor(sf::Color::Green);
		healthBar.setSize(sf::Vector2f(50, 10));
		break;
	case 4:
		healthBar.setFillColor(sf::Color::Green);
		healthBar.setSize(sf::Vector2f(40, 10));
		break;
	case 3:
		healthBar.setFillColor(sf::Color::Green);
		healthBar.setSize(sf::Vector2f(30, 10));
		break;
	case 2:
		healthBar.setFillColor(sf::Color::Yellow);
		healthBar.setSize(sf::Vector2f(20, 10));
		break;
	case 1:
		healthBar.setFillColor(sf::Color::Red);
		healthBar.setSize(sf::Vector2f(10, 10));
		break;
	case 0:
		break;
	}
	healthBar.setPosition(getPosition().x, getPosition().y - 15.0f);
	healthBarBackground.setPosition(getPosition().x, getPosition().y - 15.0f);
	count++;
}
