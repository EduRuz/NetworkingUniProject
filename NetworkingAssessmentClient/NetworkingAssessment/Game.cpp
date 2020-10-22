#include "Game.h"


/**
Sets up the window for drawing and the input class for input control
@param sf::RenderWindow* pointer to a SFML render window.
@param Input* pointer to an Input.
*/
Game::Game(sf::RenderWindow* wind, Input* in)
{
	window = wind;
	input = in;
	initialize();
}


Game::~Game()
{
}

/**
Initializes variables and classes for the game class.
*/
void Game::initialize()
{
	ArielFont.loadFromFile("font/arial.ttf");
	fpsText.setFont(ArielFont);
	fpsText.setCharacterSize(20);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setStyle(sf::Text::Bold);
	fpsText.setPosition(window->getSize().x*0.8, window->getSize().y*0.95);

	timeText.setFont(ArielFont);
	timeText.setCharacterSize(20);
	timeText.setFillColor(sf::Color::White);
	timeText.setStyle(sf::Text::Bold);
	timeText.setPosition(window->getSize().x*0.01, window->getSize().y*0.95);

	latencyText.setFont(ArielFont);
	latencyText.setCharacterSize(20);
	latencyText.setFillColor(sf::Color::White);
	latencyText.setStyle(sf::Text::Bold);
	latencyText.setPosition(window->getSize().x*0.25, window->getSize().y*0.95);

	loadingTexture.loadFromFile("Gfx/Loading.png");
	loadingsprite.setTexture(&loadingTexture);
	loadingsprite.setSize(sf::Vector2f(1250, 950));
	loadingsprite.setPosition(0, 0);

	window->clear();
	window->draw(loadingsprite);
	window->display();

	firetexture.loadFromFile("Gfx/Fire.png");
	fireSprite.setTexture(&firetexture);
	fireSprite.setSize(sf::Vector2f(30, 30));
	fireSprite.setPosition(990, 90);
	fireSprite.insertPlayerInformation(bossInfo.fireX, bossInfo.fireY, 0);

	level.initialize(window);
	player1.initialize(window, input, "Gfx/Protaginist Sprite Sheet.png", 550, 450);
	player1.setHealthValue(2);
	player2.initialize(window, input, "Gfx/BlondeSpriteSheet2.png", 650, 450);
	player2.setHealthValue(4);
	dragon.initialize(window);

	bossInfo.bossX = 1000;
	bossInfo.bossY = 50;
	dragon.setPosition(bossInfo.bossX, bossInfo.bossY);
	dragon.insertPlayerInformation(bossInfo.bossX, bossInfo.bossY, 0);

	orig = true;
	missedPacket = false;

	initNetConnection();
}

/**
Initialize the connections before starting the game to sync up the clocks.
*/
void Game::initNetConnection()
{
	socket.bind(CLIENT1PORT);
	myInfo.playerID = 1;

	do {
		startInfo.playerID = 1;
		startInfo.startMessage = "ready";
		startPacket << startInfo.playerID << startInfo.startMessage;
		socket.send(startPacket, SERVERIP, SERVERPORT);
		startPacket.clear();

		socket.receive(startPacket, recievedFromIP, recievedPort);
		startPacket >> startInfo.playerID >> startInfo.startMessage;
		startPacket.clear();

	} while (startInfo.startMessage.compare("start") != 0 && recievedFromIP != SERVERIP && recievedPort != SERVERPORT);




	socket.setBlocking(false);
	clock.restart();
	frameCount = 0;
}

/**
Called every frame to control input, used for input and to extend input to specific classes.
@param float the delta time from the games main loop.
*/
void Game::inputControl(float deltaTime)
{
	player1.inputControl(deltaTime);
}

/**
Called every frame to update variables for rendering and to extend to update to specific classes Game contains.
@param float the delta time from the games main loop.
*/
void Game::update(float deltaTime)
{
	fps = 1.0f / deltaTime;

	ss.str("");
	ss.clear();
	ss << "FPS: " << fps;
	fpsText.setString(ss.str());

	sf::Time tt = clock.getElapsedTime();
	currentTime = tt.asMilliseconds();

	if (orig) {
		connectionUpdatesOrig();
	}
	else {
		connectionUpdates();
	}

	ss.str("");
	ss.clear();
	ss << "Elapsed time: " << currentTime;
	timeText.setString(ss.str());

	if (frameCount % 60 == 0) {
		ss.str("");
		ss.clear();
		ss << "Latency: " << (currentTime - playerInfo.elapsedTime) << " ms";
		latencyText.setString(ss.str());
	}

	level.update(deltaTime);
	player1.update(deltaTime);
	player2.networkUpdate(deltaTime);
	dragon.update(deltaTime);
}

/**
Controls connection updates every frame after updating client side variables to send to the server and receive 
server variables before rendering to the window. set up to recieve every 5000ms but doesnt work as intended.
*/
void Game::connectionUpdates()
{
	//Send player information to server every frame;
	myInfo.x = player1.getPosition().x;
	myInfo.y = player1.getPosition().y;
	myInfoPacket.clear();
	myInfoPacket << myInfo.playerID << myInfo.x << myInfo.y << myInfo.elapsedTime << myInfo.type;
	socket.send(myInfoPacket, SERVERIP, SERVERPORT);

	//Recieve player 2 information every frame
	playerInfoPacket.clear();
	if (socket.receive(playerInfoPacket, recievedFromIP, recievedPort) != sf::Socket::NotReady) {
		playerInfoPacket >> tempInfo.playerID >> tempInfo.x >> tempInfo.y >> tempInfo.elapsedTime >> tempInfo.type;
		if (tempInfo.type == 1) {
			playerInfo = tempInfo;
			player2.setPosition(playerInfo.x, playerInfo.y);
		}
	}

	//Only recieve boss information every 5000 ms to test prediction.
	updatePacket.clear();
	if (socket.receive(updatePacket, recievedFromIP, recievedPort) == sf::Socket::Done) {
		updatePacket >> updateInfo.playerID >> updateInfo.startMessage;
		if (startInfo.startMessage.compare("update") == 0 && recievedFromIP == SERVERIP && recievedPort == SERVERPORT) {
			std::cout << "Update packet recieved at : " << currentTime << " ms" << "\n";


			while (socket.receive(bossPacket, recievedFromIP, recievedPort) != sf::Socket::Done) {
				bossPacket >> bossInfo.bossX >> bossInfo.bossY >> bossInfo.fireX >> bossInfo.fireY >> bossInfo.type >> bossInfo.elapsedTime;
				if (bossInfo.type == 0) {
					dragon.setPosition(bossInfo.bossX, bossInfo.bossY);
					dragon.insertPlayerInformation(bossInfo.bossX, bossInfo.bossY, bossInfo.elapsedTime);
					fireSprite.setPosition(bossInfo.fireX, bossInfo.fireY);
					fireSprite.insertPlayerInformation(bossInfo.fireX, bossInfo.fireY, bossInfo.elapsedTime);
				}
				bossPacket.clear();
			}

		}
		else {
			dragon.spritePrediction(currentTime);
			dragon.setPosition(dragon.getSpritePrediction());

			fireSprite.spritePrediction(currentTime);
			fireSprite.setPosition(fireSprite.getSpritePrediction());


		}
	}
}

/**
Original Update method for updating networking variables for sending and recieving. With simplified
prediction that is used when a boss info packet hasnt been recieved.
*/
void Game::connectionUpdatesOrig()
{
	myInfo.x = player1.getPosition().x;
	myInfo.y = player1.getPosition().y;
	myInfoPacket.clear();
	myInfoPacket << myInfo.playerID << myInfo.x << myInfo.y << myInfo.elapsedTime << myInfo.type;
	socket.send(myInfoPacket, SERVERIP, SERVERPORT);

	playerInfoPacket.clear();
	if (socket.receive(playerInfoPacket, recievedFromIP, recievedPort) != sf::Socket::NotReady) {
		playerInfoPacket >> tempInfo.playerID >> tempInfo.x >> tempInfo.y >> tempInfo.elapsedTime >> tempInfo.type;
		if (tempInfo.type == 1) {
			playerInfo = tempInfo;
			player2.setPosition(playerInfo.x, playerInfo.y);
		}
	}

	bossPacket.clear();
	if (socket.receive(bossPacket, recievedFromIP, recievedPort) != sf::Socket::NotReady) {
		bossPacket >> bossInfo.bossX >> bossInfo.bossY >> bossInfo.fireX >> bossInfo.fireY >> bossInfo.type >> bossInfo.elapsedTime;
		if (bossInfo.type == 0) {
			dragon.setPosition(bossInfo.bossX, bossInfo.bossY);
			dragon.insertPlayerInformation(bossInfo.bossX, bossInfo.bossY, bossInfo.elapsedTime);

			fireSprite.setPosition(bossInfo.fireX, bossInfo.fireY);
			fireSprite.insertPlayerInformation(bossInfo.fireX, bossInfo.fireY, bossInfo.elapsedTime);
		}
		else {
			dragon.spritePrediction(currentTime);
			dragon.setPosition(dragon.getSpritePrediction());

			fireSprite.spritePrediction(currentTime);
			fireSprite.setPosition(fireSprite.getSpritePrediction());
		}
	}
	else {
	
		dragon.spritePrediction(currentTime);
		dragon.setPosition(dragon.getSpritePrediction());

		fireSprite.spritePrediction(currentTime);
		fireSprite.setPosition(fireSprite.getSpritePrediction());
	}
}

/**
Called every frame for rendering stuff to screen after updating variables and receiving server variables.
@param float delta time from main game loop.
*/
void Game::render(float deltaTime)
{
	level.render(deltaTime);
	window->draw(fireSprite);
	window->draw(player1);
	player1.renderPlayerComponents();
	window->draw(player2);
	player2.renderPlayerComponents();
	window->draw(dragon);
	dragon.renderBossComponents();
	window->draw(fpsText);
	window->draw(timeText);
	window->draw(latencyText);
	frameCount++;
}

/**
Called when game is closed to clean up pointer variables.
*/
void Game::onExit()
{
	delete window;
	window = NULL;
}


