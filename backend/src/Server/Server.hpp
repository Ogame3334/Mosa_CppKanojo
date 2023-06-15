#pragma once

#include <memory>
#include "../Handler/HandlerBase.hpp"

namespace FruitsGroove{
    class Server{
        using HandlerPtr = std::unique_ptr<HandlerBase>;
    private:
        HandlerPtr handerInstance;
        boost::asio::ip::udp::socket sock;
    public:
        Server() = default;
        Server(HandlerPtr instance);
        ~Server() = default;
        void Start();
        void Stop();
    };
}