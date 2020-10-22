#pragma once
#include <SFML/Network.hpp>

class PlayerInfoPacket : public sf::Packet
{

public:

	struct PlayerInformation {

		int playerID;
		float x, y;
		sf::Int32 elapsedTime;
		int type = 1;

	};

	friend sf::Packet& operator <<(sf::Packet& packet, const PlayerInformation& m)
	{
		return packet << m.playerID << m.x << m.y << m.elapsedTime << m.type;
	}

	friend sf::Packet& operator >>(sf::Packet& packet, PlayerInformation& m)
	{
		return packet >> m.playerID >> m.x >> m.y >> m.elapsedTime >> m.type;
	}

};