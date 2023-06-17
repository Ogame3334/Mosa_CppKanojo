#include "src/Connection/Connection.hpp"
#include <spdlog/spdlog.h>
#include "src/Protocol/PacketParser.hpp"
#include "src/Protocol/PacketBuilder.hpp"

namespace asio = boost::asio;
using asio::ip::tcp;

namespace FruitsGroove{
    // bool SendPacket(std::unique_ptr<tcp::socket>& socket, OperationType type, std::string content){
    //     PacketBuilder packetBuilder{};
    //     packetBuilder.SetOperation(type).SetContent(content);
    //     const std::string msg = packetBuilder.Build();
    //     boost::system::error_code error;
    //     asio::write(*socket, asio::buffer(msg), error);
        

    //     if (error) {
    //         return false;
    //     }
    //     else {
    //         return true;
    //     }
    // }

    // Packet ReceivePacket(std::unique_ptr<boost::asio::ip::tcp::socket>& socket){
    //     Packet packet;
    //     asio::streambuf receive_buffer;
    //     boost::system::error_code error;
    //     asio::read(*socket, receive_buffer, asio::transfer_at_least(1), error);

    //     if (error && error != asio::error::eof) {
    //         spdlog::warn("tcp reader: read failed");
    //         packet.op = OperationType::None;
    //         packet.content = "";
    //     }
    //     else {
    //         const char* data = asio::buffer_cast<const char*>(receive_buffer.data());
    //         packet = ParsePacket(data);
    //     }

    //     return packet;
    // }
    
}