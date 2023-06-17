#pragma once

#include <boost/asio.hpp>
#include <string.h>
#include "src/Protocol/OperationType.hpp"
#include "src/Protocol/Packet.hpp"
#include "src/Protocol/PacketBuilder.hpp"

namespace FruitsGroove{
namespace Connection{
// bool SendPacket(
//     std::unique_ptr<boost::asio::ip::tcp::socket>& socket,
//     OperationType type, std::string content
// ){
//         PacketBuilder packetBuilder{};
//         packetBuilder.SetOperation(type).SetContent(content);
//         const std::string msg = packetBuilder.Build();
//         boost::system::error_code error;
//         boost::asio::write(*socket, boost::asio::buffer(msg), error);
        

//         if (error) {
//             return false;
//         }
//         else {
//             return true;
//         }
//     };
// Packet ReceivePacket(std::unique_ptr<boost::asio::ip::tcp::socket>& socket);
}
}