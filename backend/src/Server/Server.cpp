#include "Server.hpp"
#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <spdlog/spdlog.h>
#include "src/Protocol/PacketBuilder.hpp"

namespace asio = boost::asio;
using boost::asio::ip::tcp;


namespace FruitsGroove{
    Server::Server(HandlerPtr instance) : sock(this->io_service)
    {
        this->handerInstance = std::move(instance);
        this->roomManager = RoomManager();
    }

    bool Server::WaitForClient(tcp::acceptor& acc, std::unique_ptr<tcp::socket>& socket){
        boost::system::error_code error;
        acc.accept(*socket, error);

        if(error){
            spdlog::warn("tcp accepter: accept failed");
            return false;
        }
        auto endpoint = socket->remote_endpoint();
        spdlog::info("accepted from {}:{}", endpoint.address().to_string(), endpoint.port());
        
        return true;
    }

    void Server::Run(){
        using namespace boost::asio::ip;

        tcp::acceptor acc(this->io_service, tcp::endpoint(tcp::v4(), 23292));
        PacketBuilder packetBuilder{};
        boost::system::error_code error;
        std::string msg = "";

        for(;3;){ // <-可愛い！！！！
            spdlog::info("accepter start");
            auto socket1 = std::make_unique<tcp::socket>(this->io_service);
            auto socket2 = std::make_unique<tcp::socket>(this->io_service);

            if(!this->WaitForClient(acc, socket1)) continue;

            packetBuilder.SetOperation(OperationType::WaitForPlayer).SetContent("");
            msg = packetBuilder.Build();
            boost::asio::write(*socket1, boost::asio::buffer(msg), error);
            
            if(!this->WaitForClient(acc, socket2)) continue;

            packetBuilder.SetOperation(OperationType::MatchingComplete).SetContent("");
            msg = packetBuilder.Build();
            boost::asio::write(*socket1, boost::asio::buffer(msg), error);
            boost::asio::write(*socket2, boost::asio::buffer(msg), error);

            this->roomManager.createRoom(std::move(socket1), std::move(socket2));
        }
    }

    void Server::Stop(){
        this->sock.close();
    }
}