#include "Server.hpp"
#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

namespace FruitsGroove{
    Server::Server(HandlerPtr instance) : sock(this->io_service)
    {
        this->handerInstance = std::move(instance);
    }

    void Server::Start(){
        using namespace boost::asio::ip;

        this->sock = udp::socket{this->io_service, udp::endpoint(udp::v4(), 23292)};

        for(;3;){ // <-可愛い！！！！
            boost::array<char, 128> recv_buf;
            udp::endpoint endpoint;
            size_t len = sock.receive_from(boost::asio::buffer(recv_buf), endpoint);

            std::stringstream ss;
            ss.write(recv_buf.data(), len);
            this->handerInstance->Handle(ss.str());
        }
    }

    void Server::Stop(){
        this->sock.close();
    }
}