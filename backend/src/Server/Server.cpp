#include "Server.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

namespace FruitsGroove{
    Server::Server(HandlerPtr instance){
        this->handerInstance = std::move(instance);
    }

    void Server::Start(){
        using namespace boost::asio::ip;

        boost::asio::io_service io_service;
        udp::socket sock(io_service, udp::endpoint(udp::v4(), 23292));

        std::cout << "動き始めたよ！！" << std::endl;

        for(;3;){ // <-可愛い！！！！
            boost::array<char, 128> recv_buf;
            udp::endpoint endpoint;
            size_t len = sock.receive_from(boost::asio::buffer(recv_buf), endpoint);

            std::cout.write(recv_buf.data(), len);
        }
    }

    void Server::Stop(){

    }
}