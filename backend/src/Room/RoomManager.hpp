#pragma once

#include <vector>
#include <memory>
#include <thread>
#include "src/Room/Room.hpp"
#include "src/Handler/PacketHandler.hpp"

namespace FruitsGroove{
    class RoomManager{
        using SocketPtr = std::unique_ptr<boost::asio::ip::tcp::socket>;
        using RoomPtr = std::unique_ptr<Room>;
    private:
        std::vector<RoomPtr> rooms;
        PacketHandler packetHandler{};
    public:
        RoomManager();
        void createRoom(SocketPtr socket1, SocketPtr socket2);
    };
}