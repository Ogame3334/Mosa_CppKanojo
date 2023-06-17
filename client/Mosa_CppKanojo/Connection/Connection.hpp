#include <Siv3D.hpp>

#include "../Protocol/OperationType.hpp"
#include "../Protocol/PacketBuilder.hpp"

namespace FruitsGroove {
	namespace Connection {
		class ServerConnection {
		private:
			const IPv4Address ip{ { 219, 94, 241, 220 } };
			const uint16 port = 23292;
			TCPClient client;
			PacketBuilder packetBuilder{};
		public:
			ServerConnection() {}
			bool sendPacket(OperationType type, StringView content);
		};
	}
}
