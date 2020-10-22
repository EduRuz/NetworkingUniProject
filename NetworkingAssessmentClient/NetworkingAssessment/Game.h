#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Input.h"
#include "GameSprite.h"
#include "PlayerCharacter.h"
#include "Boss.h"
#include "Level.h"
#include "Collision.h"
#include "NetworkInfoPacket.h"
#include "BossInfoPacket.h"
#include "PlayerInfoPacket.h"
#include <vector>
#include <sstream>
#include <iostream>
#include "FireBlast.h"

class Game
{
public:
	Game(sf::RenderWindow* wind, Input* in);
	~Game();
	void initialize();
	void initNetConnection();
	void inputControl(float deltaTime);
	void update(float deltaTime);
	void connectionUpdates();
	void connectionUpdatesOrig();
	void render(float deltaTime);
	void onExit();

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

	NetworkInformation startInfo;
	NetworkInfoPacket startPacket;

	NetworkInformation updateInfo;
	NetworkInfoPacket updatePacket;
	bool updateRecieved;

	BossInformation bossInfo;
	BossInfoPacket bossPacket;

	PlayerInformation myInfo;
	PlayerInfoPacket myInfoPacket;
	PlayerInformation tempInfo;

	PlayerInformation playerInfo;
	PlayerInfoPacket playerInfoPacket;


	sf::UdpSocket socket;
	sf::IpAddress recievedFromIP;
	unsigned short recievedPort;

	Level level;
	PlayerCharacter player1;
	PlayerCharacter player2;
	Boss dragon;

	sf::RenderWindow* window;
	Input* input;

	sf::Texture loadingTexture;
	sf::RectangleShape loadingsprite;

	FireBlast fireSprite;
	sf::Texture firetexture;

	float fps;
	sf::Font ArielFont;
	sf::Text fpsText;
	sf::Text timeText;
	sf::Text latencyText;
	std::ostringstream ss;

	sf::Vertex line[2];

	sf::Clock clock;
	sf::Int32 currentTime;

	int frameCount;

	bool orig;
	bool missedPacket;
};

