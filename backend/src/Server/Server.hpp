#pragma once

#include <boost/asio.hpp>
#include <memory>
#include "../Handler/HandlerBase.hpp"

namespace FruitsGroove{
    class Server{
        using HandlerPtr = std::unique_ptr<HandlerBase>;
    private:
        HandlerPtr handerInstance;
        boost::asio::ip::udp::socket sock;
    public:
        Server() = delete;
        Server(HandlerPtr instance);
        ~Server() = default;
        void Start();
        void Stop();
    };
}