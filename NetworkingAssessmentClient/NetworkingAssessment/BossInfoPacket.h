#pragma once
#include <SFML/Network.hpp>

class BossInfoPacket : public sf::Packet
{
public:
	struct BossInformation {

		float bossX, bossY;
		float fireX, fireY;
		int type = 0;
		sf::Int32 elapsedTime;

	};

	friend sf::Packet& operator <<(sf::Packet& packet, const BossInformation& m)
	{
		return packet << m.bossX << m.bossY << m.fireX << m.fireY << m.type << m.elapsedTime;
	}

	friend sf::Packet& operator >>(sf::Packet& packet, BossInformation& m)
	{
		return packet >> m.bossX >> m.bossY >> m.fireX >> m.fireY >> m.type >> m.elapsedTime;
	}


};