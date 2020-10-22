#pragma once
#include <SFML/Network.hpp>

class NetworkInfoPacket : public sf::Packet
{

public:

	struct NetworkInformation {
		int playerID;
		std::string startMessage;
	};

	friend sf::Packet& operator <<(sf::Packet& packet, const NetworkInformation& m)
	{
		return packet << m.playerID <<m.startMessage;
	}

	friend sf::Packet& operator >>(sf::Packet& packet, NetworkInformation& m)
	{
		return packet >> m.playerID >> m.startMessage;
	}


};