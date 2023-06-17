#pragma once

#include <boost/asio.hpp>
#include <string.h>
#include "src/Protocol/OperationType.hpp"
#include "src/Protocol/Packet.hpp"

namespace FruitsGroove{
namespace Connection{
bool SendPacket(
    std::unique_ptr<boost::asio::ip::tcp::socket>& socket,
    OperationType type, std::string content
);
Packet ReceivePacket(std::unique_ptr<boost::asio::ip::tcp::socket>& socket);
}
}