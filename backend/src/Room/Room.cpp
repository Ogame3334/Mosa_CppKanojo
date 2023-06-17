#include "src/Room/Room.hpp"
#include "src/Connection/Connection.hpp"
#include "src/Protocol/PacketParser.hpp"
#include "src/Handler/PacketHandler.hpp"

namespace FruitsGroove{
    Room::Room(std::array<SocketPtr, 2> sockets){
        this->socketArray = std::move(sockets);
        this->threadArray[0] = std::thread([&](){this->SocketDataProcessor(this->socketArray[0], this->socketArray[1]);});
        this->threadArray[1] = std::thread([&](){this->SocketDataProcessor(this->socketArray[1], this->socketArray[0]);});
    }

    void Room::SocketDataProcessor(SocketPtr& dest_socket, SocketPtr& source_socket){
        PacketHandler packetHandler{};
        Packet packet;
        asio::streambuf receive_buffer;
        boost::system::error_code error;
        asio::read(*source_socket, receive_buffer, asio::transfer_at_least(1), error);

        if (error && error != asio::error::eof) {
            spdlog::warn("tcp reader: read failed");
            packet.op = OperationType::None;
            packet.content = "";
        }
        else {
            const char* data = asio::buffer_cast<const char*>(receive_buffer.data());
            packet = ParsePacket(data);
        }
        packetHandler.Handle(packet, dest_socket, *this);
    }
}