#pragma once

#include <boost/asio.hpp>
#include <memory>
#include "../Handler/HandlerBase.hpp"
#include "src/Room/RoomManager.hpp"

namespace FruitsGroove{
    class Server{
        using HandlerPtr = std::unique_ptr<HandlerBase>;
    private:
        HandlerPtr handerInstance;
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::socket sock;
        RoomManager roomManager;

        bool WaitForClient(boost::asio::ip::tcp::acceptor& acc, std::unique_ptr<boost::asio::ip::tcp::socket>& socket);
    public:
        Server() = delete;
        Server(HandlerPtr instance);
        ~Server() = default;
        void Run();
        void Stop();
    };
}