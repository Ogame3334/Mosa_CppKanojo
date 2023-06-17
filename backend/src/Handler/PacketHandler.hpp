#pragma once
#include "./HandlerBase.hpp"
#include <string_view>

namespace FruitsGroove{
    class PacketHandler: public HandlerBase{
    public:
        void Handle(std::unique_ptr<boost::asio::ip::tcp::socket> socket) override{
        };
    };
}