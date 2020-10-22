#pragma once
#include  <SFML/Graphics.hpp>
#include  <SFML/Network.hpp>
#include "Input.h"
#include <sstream>
#include <iostream>
#include "NetworkInfoPacket.h"
#include "BossInfoPacket.h"
#include "PlayerInfoPacket.h"
#include <string>

class Server
{
public:
	Server(sf::RenderWindow* wind, Input* in);
	~Server();

	void initialize();
	void initServer();
	void update(float deltaTime);
	void connectionUpdates(float deltaTime);
	void connectionUpdatesOrig(float deltaTime);
	void render();
	void playerManager(float deltaTime);
	void bossManager(float deltaTime);
	void fireManager(float deltaTime);

	sf::RenderWindow* window;
	Input* input;

private:
	
	const int SERVERPORT = 60501;
	const int CLIENT1PORT = 50994;
	const int CLIENT2PORT = 50995;
	const sf::IpAddress SERVERIP = "192.168.0.17";
	const sf::IpAddress CLIENT1IP = "192.168.0.17";
	const sf::IpAddress CLIENT2IP = "192.168.0.17";

	//const int SERVERPORT = 55001;
	//const int CLIENT1PORT = 55002;
	//const int CLIENT2PORT = 55003;
	//const sf::IpAddress SERVERIP = "127.0.0.1";
	//const sf::IpAddress CLIENT1IP = "127.0.0.1";
	//const sf::IpAddress CLIENT2IP = "127.0.0.1";

	struct NetworkInformation {
		int playerID;
		std::string startMessage;
	};

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
		sf::Int32 elapsedTime;

	};

	unsigned short client1Port;
	sf::IpAddress client1IP;
	unsigned short client2Port;
	sf::IpAddress client2IP;


	float fps;
	sf::Font ArielFont;
	sf::Text fpsText;
	sf::Text timeText;
	std::ostringstream ss;

	sf::RectangleShape background;
	sf::Text bossText;
	sf::Text player1Text;
	sf::Text player2Text;
	sf::Text fireText;

	//Networking Information
	sf::Clock serverClock;
	sf::Int32 currentTime;
	sf::Int32 updateTime;
	
	NetworkInfoPacket startPacket;
	NetworkInformation startInfo;

	NetworkInformation updateInfo;
	NetworkInfoPacket updatePacket;

	sf::UdpSocket socket;
	sf::IpAddress IP;
	PlayerInformation player1Info;
	PlayerInformation player2Info;
	PlayerInformation playerTempInfo;
	unsigned short clientPort;
	BossInfoPacket bossPacket;
	PlayerInfoPacket player1Packet;
	PlayerInfoPacket player2Packet;
	PlayerInformation temppInfo;

	//Boss Variables
	BossInformation bossInfo;
	bool bossMovingUp;
	float movementSpeed;

	int count = 0;

	bool orig;
};

