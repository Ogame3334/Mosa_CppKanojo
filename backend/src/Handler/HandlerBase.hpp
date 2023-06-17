#pragma once
#include <string>
#include <string_view>
#include <boost/asio.hpp>
#include <memory>

namespace FruitsGroove{
    class HandlerBase{
    public:
    virtual void Handle(std::unique_ptr<boost::asio::ip::tcp::socket> socket) = 0;
    };
}

