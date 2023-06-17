#pragma once
#include <string>
#include <string_view>
#include <boost/asio.hpp>
#include <memory>
#include "src/Protocol/Packet.hpp"

namespace asio = boost::asio;
using asio::ip::tcp;

namespace FruitsGroove{
    class HandlerBase{
    public:
    virtual void Handle(const Packet& packet, std::unique_ptr<tcp::socket>& sock) = 0;
    };
}

