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
#include "src/Handler/PacketHandler.hpp"
#include <array>
#include <string_view>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include <thread>
#include <string>

namespace FruitsGroove{
class Room{
    using SocketPtr = std::unique_ptr<boost::asio::ip::tcp::socket>;
private:
    std::array<SocketPtr, 2> socketArray;
    std::array<std::thread, 2> threadArray;
    std::array<std::string, 2> songsArray;
    void SocketDataProcessor(SocketPtr& dest_socket, SocketPtr& source_socket);
public:
    Room() = delete;
    Room(std::array<SocketPtr, 2>&& socketArray):
        socketArray(std::move(socketArray))
        {}
};
}
