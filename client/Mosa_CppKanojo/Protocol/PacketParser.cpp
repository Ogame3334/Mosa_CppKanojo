#include "PacketParser.hpp"

namespace FruitsGroove{
Packet ParsePacket(std::string_view rawString){
    Packet packet;
	try{
		packet.op = static_cast<OperationType>(stoi(std::string{rawString.substr(0, 2)}));
	}catch(...){
		packet.op = OperationType::None;
	}
    packet.content = rawString.substr(2);
    return packet;
}
}