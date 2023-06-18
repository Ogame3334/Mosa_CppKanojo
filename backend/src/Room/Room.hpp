//#include <memory>
//#include <boost/asio.hpp>
//#include <array>

//namespace asio = boost::asio;
//using asio::ip::tcp;

//namespace FruitsGroove{
    //class Room{
        //std:
    //public:
        //Room(std::unique_ptr<tcp::socket>s1, std::unique_ptr<tcp::socket>s2){

        //}



    //};

//}

#pragma once
#include <array>
#include <string_view>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include <thread>
#include <string>
#include "src/Handler/PacketHandler.hpp"

namespace FruitsGroove{
class Room{
    using SocketPtr = std::unique_ptr<boost::asio::ip::tcp::socket>;
private:
    std::array<SocketPtr, 2> socketArray;
    std::array<std::thread, 2> threadArray;
    PacketHandler packetHandler;
    void SocketDataProcessor(SocketPtr& dest_socket, SocketPtr& source_socket);
public:
    std::vector<std::string> songsArray;
    Room() = delete;
    Room(std::array<SocketPtr, 2>&& sockets, PacketHandler& ph);
};
}
