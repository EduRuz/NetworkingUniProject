#include "Level.h"



Level::Level()
{
	
}


Level::~Level()
{
}

/**
Initializes variables and classes from the Level class to use.
@param sf::RenderWindow* pointer to the window for drawing to.
*/
void Level::initialize(sf::RenderWindow* wind)
{
	window = wind;

	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 25; j++) {
			switch (map[j][i]) {
			case(00): {
				sprites[j][i] = &waterSprite;
				break;
			}
			case(11):
				sprites[j][i] = &bottomLeftWaterCornerSprite;
				break;
			case(12):
				sprites[j][i] = &leftWaterWallSprite;
				break;
			case(13):
				sprites[j][i] = &topLeftWaterCornerSprite;
				break;
			case(14):
				sprites[j][i] = &topWaterWallSprite;
				break;
			case(15):
				sprites[j][i] = &topRightWaterCornerSprite;
				break;
			case(16):
				sprites[j][i] = &rightWaterWallSprite;
				break;
			case(17):
				sprites[j][i] = &bottomRightWaterCornerSprite;
				break;
			case(18):
				sprites[j][i] = &BottomWaterWallSprite;
				break;
			case(19):
				sprites[j][i] = &sandSprite;
				break;
			case(10):
				sprites[j][i] = &grassSprite;
				break;
			case(21):
				sprites[j][i] = &flowerSprite;
				break;
			}
		}
	}

	waterSprite.initialize(00);
	bottomLeftWaterCornerSprite.initialize(11);
	leftWaterWallSprite.initialize(12);
	topLeftWaterCornerSprite.initialize(13);
	topWaterWallSprite.initialize(14);
	topRightWaterCornerSprite.initialize(15);
	rightWaterWallSprite.initialize(16);
	bottomRightWaterCornerSprite.initialize(17);
	BottomWaterWallSprite.initialize(18);
	flowerSprite.initialize();

	grassTexture.loadFromFile("Gfx/Grass.png");
	grassSprite.setTexture(&grassTexture);
	grassSprite.setSize(sf::Vector2f(50, 50));
	sandTexture.loadFromFile("Gfx/Sand2.png");
	sandSprite.setTexture(&sandTexture);
	sandSprite.setSize(sf::Vector2f(50,50));

	piller1.initialize(810, 150);
	piller2.initialize(810, 400);
	piller3.initialize(810, 650);
}

/**
Called every frame to update variables for rendering and to extend to update to specific classes Level contains.
@param float the delta time from the games main loop.
*/
void Level::update(float deltaTime)
{
	animations(deltaTime);
}

/**
Called every frame for rendering stuff to screen after updating variables.
@param float delta time from main game loop.
*/
void Level::render(float deltaTime)
{
	xPosition = 0.0f;
	yPosition = 0.0f;

	for (int i = 0; i < 19; i++) {
		xPosition = 0.0f;
		for (int j = 0; j < 25; j++) {
		
			switch (map[i][j]) {
			case(00):
				waterSprite.setPosition(xPosition, yPosition);
				window->draw(waterSprite);
				break;
			case(11):
				bottomLeftWaterCornerSprite.setPosition(xPosition, yPosition);
				window->draw(bottomLeftWaterCornerSprite);
				break;
			case(12):
				leftWaterWallSprite.setPosition(xPosition, yPosition);
				window->draw(leftWaterWallSprite);
				break;
			case(13):
				topLeftWaterCornerSprite.setPosition(xPosition, yPosition);
				window->draw(topLeftWaterCornerSprite);
				break;
			case(14):
				topWaterWallSprite.setPosition(xPosition, yPosition);
				window->draw(topWaterWallSprite);
				break;
			case(15):
				topRightWaterCornerSprite.setPosition(xPosition, yPosition);
				window->draw(topRightWaterCornerSprite);
				break;
			case(16):
				rightWaterWallSprite.setPosition(xPosition, yPosition);
				window->draw(rightWaterWallSprite);
				break;
			case(17):
				/*if (bottomRightBounds.boundFound == false) {
					bottomRightBounds.xBound = xPosition;
					bottomRightBounds.yBound = yPosition;
					bottomRightBounds.boundFound = true;
				}*/
				bottomRightWaterCornerSprite.setPosition(xPosition, yPosition);
				window->draw(bottomRightWaterCornerSprite);
				break;
			case(18):
				BottomWaterWallSprite.setPosition(xPosition, yPosition);
				window->draw(BottomWaterWallSprite);
				break;
			case(19):
				sandSprite.setPosition(xPosition, yPosition);
				window->draw(sandSprite);
				break;
			case(10):
				grassSprite.setPosition(xPosition, yPosition);
				window->draw(grassSprite);
				break;
			case(21):
				/*if (topLeftBounds.boundFound == false) {
					topLeftBounds.xBound = xPosition;
					topLeftBounds.yBound = yPosition;
					topLeftBounds.boundFound = true;
				}*/
				flowerSprite.setPosition(xPosition, yPosition);
				window->draw(flowerSprite);
				break;
			}
			xPosition += 50;
		}
		yPosition += 50;
	}

	window->draw(piller1);
	window->draw(piller2);
	window->draw(piller3);
}

/**
Called when game is closed to clean up pointer variables.
*/
void Level::onExit()
{
	for (int i = 0; i < gridAmount; i++) {

		for (int j = 0; j < gridAmount; j++) {
		
			delete sprites[i][j];
			sprites[i][j] = NULL;
		}
	}

	delete window;
	window = NULL;
}

/**
Called to update the frames for the animations owned by Level.
@param float delta time to be passed through for animation updates.
*/
void Level::animations(float deltaTime)
{
	waterSprite.update(deltaTime);
	flowerSprite.update(deltaTime);
	topWaterWallSprite.update(deltaTime);
	BottomWaterWallSprite.update(deltaTime);
	leftWaterWallSprite.update(deltaTime);
	rightWaterWallSprite.update(deltaTime);
	topLeftWaterCornerSprite.update(deltaTime);
	topRightWaterCornerSprite.update(deltaTime);
	bottomRightWaterCornerSprite.update(deltaTime);
	bottomLeftWaterCornerSprite.update(deltaTime);
}
