#include "Server.h"

/**
Constructor for the Server Class.
@param sf::RenderWindow* pointer for drawing to window.
@param Input for keyboard and mouse support.
*/
Server::Server(sf::RenderWindow* wind, Input* in)
{
	window = wind;
	input = in;
	initialize();
}

Server::~Server()
{
}

/**
Initializes the variables for the Server.
*/
void Server::initialize()
{
	ArielFont.loadFromFile("font/arial.ttf");
	fpsText.setFont(ArielFont);
	fpsText.setCharacterSize(20);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setStyle(sf::Text::Bold);
	fpsText.setPosition(window->getSize().x*0.75, window->getSize().y*0.95);

	timeText.setFont(ArielFont);
	timeText.setCharacterSize(20);
	timeText.setFillColor(sf::Color::White);
	timeText.setStyle(sf::Text::Bold);
	timeText.setPosition(window->getSize().x*0.1, window->getSize().y*0.95);

	bossText.setFont(ArielFont);
	bossText.setFillColor(sf::Color::Blue);
	bossText.setCharacterSize(20);
	bossText.setString("Boss");

	player1Text.setFont(ArielFont);
	player1Text.setFillColor(sf::Color::Green);
	player1Text.setCharacterSize(20);
	player1Text.setString("Player 1");

	player2Text.setFont(ArielFont);
	player2Text.setFillColor(sf::Color::Yellow);
	player2Text.setCharacterSize(20);
	player2Text.setString("Player 2");

	fireText.setFont(ArielFont);
	fireText.setFillColor(sf::Color::Red);
	fireText.setCharacterSize(20);
	fireText.setString("Fire");


	background.setFillColor(sf::Color::Black);
	background.setSize(sf::Vector2f(625, 475));
	background.setPosition(0,0);

	bossInfo.bossX = 1000;
	bossInfo.bossY = 50;
	bossInfo.fireX = 990;
	bossInfo.fireY = 90;
	bossMovingUp = false;
	movementSpeed = 50.0;

	player1Info.x = 550;
	player1Info.y = 450;
	player2Info.x = 650;
	player2Info.y = 450;

	orig = true;
	initServer();
}

/**
Initilizes the client connections to the server to try and send a synchronised start message to sync up the start times.
*/
void Server::initServer()
{
	socket.bind(SERVERPORT);

	do {
		std::cout << "Waiting for player 1 to connect" << "\n";
		socket.receive(startPacket, client1IP, client1Port);
		startPacket >> startInfo.playerID >> startInfo.startMessage;
	} while (startInfo.playerID != 1 && startInfo.startMessage.compare("ready") != 0);
	startPacket.clear();
	std::cout << "player " << startInfo.playerID << " is connected!" << "\n";

	do {
		std::cout << "Waiting for player 2 to connect" << "\n";
		socket.receive(startPacket, client2IP, client2Port);
		startPacket >> startInfo.playerID >> startInfo.startMessage;
	} while (startInfo.playerID != 2 && startInfo.startMessage.compare("ready") != 0);
	startPacket.clear();
	std::cout << "player " << startInfo.playerID << " is connected!" << "\n";

	startInfo.playerID = 0;
	startInfo.startMessage = "start";
	startPacket << startInfo.playerID << startInfo.startMessage;

	socket.send(startPacket, client1IP, client1Port);
	socket.send(startPacket, client2IP, client2Port);


	socket.setBlocking(false);
	updateTime = 0;
	serverClock.restart();

}

/**
Update method called every frame for updating Class Variables.
float delta time from the main game loop.
*/
void Server::update(float deltaTime)
{
	fps = 1.0f / deltaTime;

	ss.str("");
	ss.clear();
	ss << "FPS: " << fps;
	fpsText.setString(ss.str());

	sf::Time tt = serverClock.getElapsedTime();
	currentTime = tt.asMilliseconds();

	if (orig) {
		connectionUpdatesOrig(deltaTime);
	}
	else {
		connectionUpdates(deltaTime);
	}

	ss.str("");
	ss.clear();
	ss << "Elapsed time: " << currentTime << " ms";
	timeText.setString(ss.str());
	
	bossText.setPosition((bossInfo.bossX / 2), (bossInfo.bossY / 2));
	player1Text.setPosition((player1Info.x / 2), (player1Info.y / 2));
	player2Text.setPosition((player2Info.x / 2), (player2Info.y / 2));
	fireText.setPosition((bossInfo.fireX / 2), (bossInfo.fireY / 2));
}

/**
Update method for updating networking variables for sending and recieving.
This was an attempt at sending a message every 5000 ms that didnt work.
float delta time from the main game loop.
*/
void Server::connectionUpdates(float deltaTime)
{
	fireManager(deltaTime);//Needs to be after player
	bossManager(deltaTime);//fire needs to be calculated first
	playerManager(deltaTime);//Needs to be first

	updateInfo.playerID = 0;
	

	if (currentTime >= updateTime) {
		updateInfo.startMessage = "update";
		updatePacket.clear();
		updatePacket << updateInfo.playerID << updateInfo.startMessage;

		//Send Update message
		while (socket.send(updatePacket, client2IP, client2Port) != sf::Socket::Done);
		while (socket.send(updatePacket, client1IP, client1Port) != sf::Socket::Done);

		//Send boss data package
		while (socket.send(bossPacket, CLIENT1IP, CLIENT1PORT) != sf::Socket::Done);
		while (socket.send(bossPacket, CLIENT2IP, CLIENT2PORT) != sf::Socket::Done);

		updateTime += 5000;
		std::cout << "Update Packet sent at : " << currentTime << " ms" << "\n";
	}
	else {
		updateInfo.startMessage = "dont update";
		updatePacket.clear();
		updatePacket << updateInfo.playerID << updateInfo.startMessage;

		// Send dont update package
		while (socket.send(updatePacket, client2IP, client2Port) != sf::Socket::Done);
		while (socket.send(updatePacket, client1IP, client1Port) != sf::Socket::Done);
	}
}

/**
Original Update method for updating networking variables for sending and recieving.
float delta time from the main game loop.
*/
void Server::connectionUpdatesOrig(float deltaTime)
{
	playerManager(deltaTime);//Needs to be first
	fireManager(deltaTime);//Needs to be after player
	bossManager(deltaTime);//fire needs to be calculated first

	while (socket.send(bossPacket, CLIENT1IP, CLIENT1PORT) != sf::Socket::Done);
	while (socket.send(bossPacket, CLIENT2IP, CLIENT2PORT) != sf::Socket::Done);
}

/**
Called every frame to render to screen.
*/
void Server::render()
{
	window->draw(background);
	window->draw(bossText);
	window->draw(player1Text);
	window->draw(player2Text);
	window->draw(fireText);
	window->draw(fpsText);
	window->draw(timeText);
}

/**
Method to manage and send the variables for the manager to the client versions of the game. should be called after 
PlayerManager and FireManager for max efficiency for networking order.
*/
void Server::bossManager(float deltaTime)
{
	if (bossInfo.bossY <= 50) {
		bossMovingUp = false;
	}

	if (bossInfo.bossY >= 700) {
		bossMovingUp = true;
	}

	if (bossMovingUp) {
		bossInfo.bossY -= (movementSpeed * deltaTime);
	}
	else {
		bossInfo.bossY += (movementSpeed * deltaTime);
	}

	bossInfo.elapsedTime = currentTime;

	bossPacket.clear();
	bossPacket << bossInfo.bossX << bossInfo.bossY << bossInfo.fireX << bossInfo.fireY << bossInfo.type << bossInfo.elapsedTime;

}

/**
Method for controlling the fire to follow the player. Should be called before BossManager and after PlayerManager 
for max efficiency for networking order.
@param float delta time for moving the fire.
*/
void Server::fireManager(float deltaTime)
{
	/*float A1 = (bossInfo.fireX - player1Info.x) * (bossInfo.fireX - player1Info.x);
	float B1 = (bossInfo.fireY - player1Info.y) * (bossInfo.fireY - player1Info.y);
	float C1 = A1 + B1;
	float distBetweenFireP1 = sqrt(C1);*/

	if (bossInfo.fireX < player1Info.x) {
		bossInfo.fireX += (movementSpeed * deltaTime);
	}
	else {
		bossInfo.fireX -= (movementSpeed * deltaTime);
	}

	if (bossInfo.fireY < player1Info.y) {
		bossInfo.fireY += (movementSpeed * deltaTime);
	}
	else {
		bossInfo.fireY -= (movementSpeed * deltaTime);
	}
}

/**
Method for recieving and sending player information to the Clients. Should be called before bossManager and fireManager
for max efficiency for networking order.
@param float delta time for controlling player movement.
*/
void Server::playerManager(float deltaTime)
{
	PlayerInfoPacket tempPacket;

	socket.receive(tempPacket, IP, clientPort);
	tempPacket >> playerTempInfo.playerID >> playerTempInfo.x >> playerTempInfo.y >> playerTempInfo.elapsedTime >> playerTempInfo.type;
	if (playerTempInfo.playerID == 1) {
		player1Info = playerTempInfo;
		player1Info.elapsedTime = currentTime;
		player1Packet << player1Info.playerID << player1Info.x << player1Info.y << player1Info.elapsedTime << player1Info.type;
		while (socket.send(player1Packet, CLIENT2IP, CLIENT2PORT) != sf::Socket::Done);
		player1Packet.clear();
	}
	tempPacket.clear();

	socket.receive(tempPacket, IP, clientPort);
	tempPacket >> playerTempInfo.playerID >> playerTempInfo.x >> playerTempInfo.y >> playerTempInfo.elapsedTime >> playerTempInfo.type;
	if (playerTempInfo.playerID == 2) {
		player2Info = playerTempInfo;
		player2Info.elapsedTime = currentTime;
		player2Packet << player2Info.playerID << player2Info.x << player2Info.y << player2Info.elapsedTime << player2Info.type;
		while (socket.send(player2Packet, CLIENT1IP, CLIENT1PORT) != sf::Socket::Done);
		player2Packet.clear();
	}
	tempPacket.clear();

	if (count % 60 == 0) {
		std::cout << "Player ID : " << player1Info.playerID << " X position: " << player1Info.x << " Y position: " << player1Info.y << " Time Stamp: " << player1Info.elapsedTime <<"\n";
		std::cout << "Player ID : " << player2Info.playerID << " X position: " << player2Info.x << " Y position: " << player2Info.y << " Time Stamp: " << player2Info.elapsedTime << "\n";
	}

	count++;
}

