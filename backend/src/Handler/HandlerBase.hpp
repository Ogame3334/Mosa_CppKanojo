#pragma once
#include <string>
#include <string_view>
#include <boost/asio.hpp>
#include <memory>
#include "src/Protocol/Packet.hpp"
#include "src/Room/Room.hpp"

namespace asio = boost::asio;
using asio::ip::tcp;

namespace FruitsGroove{
    class HandlerBase{
    public:
    virtual void Handle(Packet packet, std::unique_ptr<tcp::socket>& socket, Room& room) = 0;
    };
}

