#include "Connection.hpp"
#include "../Protocol/PacketParser.hpp"

namespace FruitsGroove {
	namespace Connection {
		bool ServerConnection::sendPacket(OperationType type, StringView content) {
			bool couldConnect = false;
			this->client.connect(this->ip, this->port);

			this->packetBuilder.SetOperation(type).SetContent(content.narrow());
			std::string packet = this->packetBuilder.Build();

			if (client.isConnected())
			{
				client.send(packet.c_str());
				couldConnect = true;
			}

			if (client.hasError()) // 切断/接続エラー
			{
				client.disconnect();
			}

			return couldConnect;
		}

		bool ServerConnection::recievePacket(Packet& packet) {
			const char* recievedPacket;
			if(client.read(recievedPacket)){
				return false;
			}
			packet = ParsePacket(recievedPacket);
			return true;
		}
	}
}
