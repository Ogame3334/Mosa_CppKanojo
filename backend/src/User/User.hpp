#pragma once
#include <string>
#include <boost/asio.hpp>

using namespace boost::asio::ip;
namespace asio = boost::asio;

namespace FruitsGroove{
struct User{
    std::string id;
    std::string name;
    boost::asio::ip::tcp::endpoint endpoint;
    tcp::socket socket;
};
}