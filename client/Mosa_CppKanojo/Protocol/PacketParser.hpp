#pragma once 
#include "Packet.hpp"
#include <string_view>
#include <string>

namespace FruitsGroove{
Packet ParsePacket(std::string_view rawString);
}