#pragma once 
#include "Packet.hpp"
#include <string_view>
#include <string>

namespace FruitsGroove{
Packet ParsePacket(std::string_view rawString){
    Packet packet;
    packet.op = static_cast<OperationType>(stoi(std::string{rawString.substr(0, 2)}));
    packet.content = rawString.substr(2);
    return packet;
}
}