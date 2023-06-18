#include "Connection.hpp"
#include "../Protocol/PacketParser.hpp"

namespace FruitsGroove {
	namespace Connection {
		bool ServerConnection::connect(){
			this->client.connect(this->ip, this->port);
			bool couldConnect = false;
			if (client.isConnected())
			{
				return true;
			}
			if (client.hasError()) // 切断/接続エラー
			{
				client.disconnect();
			}

			return couldConnect;
		}
		bool ServerConnection::sendPacket(OperationType type, StringView content) {
			bool couldConnect = false;

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

		bool ServerConnection::receivePacket(Packet& packet) {
			const char* recievedPacket;
			constexpr int sz = 100;
			char buffer[100];

			if(client.read(buffer, sz)){
				return false;
			}
			packet = ParsePacket(buffer);
			return true;
		}
	}
}
