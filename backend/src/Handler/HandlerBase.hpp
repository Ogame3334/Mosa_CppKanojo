#pragma once
#include <string>
#include <string_view>
#include <boost/asio.hpp>
#include <memory>

namespace asio = boost::asio;
using asio::ip::tcp;

namespace FruitsGroove{
    class HandlerBase{
    public:
    virtual void Handle(std::string_view) = 0;
    };
}

