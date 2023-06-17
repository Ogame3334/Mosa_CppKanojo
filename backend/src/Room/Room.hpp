#pragma once
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
    Room(std::array<SocketPtr, 2> sockets);
};
}
