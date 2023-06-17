#include "Server.hpp"
#include "src/Handler/HandlerProcessExecuter.hpp"
#include "src/Room/Room.hpp"
#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <spdlog/spdlog.h>
#include <thread>
#include "src/Operation/NoticeIDAndName.hpp"
#include "src/Operation/SelectSong.hpp"
#include "src/Operation/ClientReady.hpp"
#include "src/Operation/CurrentCombo.hpp"
#include "src/Operation/CurrentScore.hpp"
#include "src/Operation/GameEnd.hpp"

namespace asio = boost::asio;
using boost::asio::ip::tcp;


namespace FruitsGroove{
    Server::Server(HandlerPtr instance) : sock(this->io_service)
    {
        this->handerInstance = std::move(instance);
    }

    void Server::Start(){
        using namespace boost::asio::ip;

        tcp::acceptor acc(this->io_service, tcp::endpoint(tcp::v4(), 23292));
        HandlerProcessExecuter handlerExecuter;

        for(;3;){ // <-可愛い！！！！
            spdlog::info("accepter start");
            auto socket = std::make_unique<tcp::socket>(this->io_service);

            boost::system::error_code error;
            acc.accept(*socket, error);

            if(error){
                spdlog::warn("tcp accepter: accept failed");
                continue;
            }
            auto endpoint = socket->remote_endpoint();
            spdlog::info("accepted from {}:{}", endpoint.address().to_string(), endpoint.port());
            asio::write(*socket, asio::buffer("01"), error);

            spdlog::info("accepter start");
            auto socket2 = std::make_unique<tcp::socket>(this->io_service);

            acc.accept(*socket2, error);

            if(error){
                spdlog::warn("tcp accepter: accept failed");
                continue;
            }
            endpoint = socket2->remote_endpoint();
            spdlog::info("accepted from {}:{}", endpoint.address().to_string(), endpoint.port());
            PacketHandler packetHandler;
            asio::write(*socket, asio::buffer("03"), error);
            asio::write(*socket2, asio::buffer("03"), error);
            asio::write(*socket, asio::buffer("05"), error);
            asio::write(*socket2, asio::buffer("05"), error);

            packetHandler.AddOperation(std::make_shared<ClientReady>());
            packetHandler.AddOperation(std::make_shared<CurrentCombo>());
            packetHandler.AddOperation(std::make_shared<CurrentScore>());
            packetHandler.AddOperation(std::make_shared<GameEnd>());
            packetHandler.AddOperation(std::make_shared<NoticeIDAndName>());
            packetHandler.AddOperation(std::make_shared<SelectSong>());

            auto socketConnectionFunc = [&](std::unique_ptr<tcp::socket>& s1, std::unique_ptr<tcp::socket>& s2){
                while(true){
                        // メッセージ受信
                    asio::streambuf receive_buffer;
                    boost::system::error_code error;
                    asio::read(*s1, receive_buffer, asio::transfer_at_least(1), error);

                    if (error && error != asio::error::eof) {
                        continue;
                    }
                    const char* data = asio::buffer_cast<const char*>(receive_buffer.data());
                    auto packet = ParsePacket(data);
                    packetHandler.Handle(packet, s2);
                    }
                };
            
            auto th1 = std::thread([&](){
                socketConnectionFunc(socket, socket2);
            });
            auto th2 = std::thread([&](){
                socketConnectionFunc(socket2, socket);
            });
            th1.join();




            //// メッセージ受信
            //asio::streambuf receive_buffer;
            //asio::read(*socket, receive_buffer, asio::transfer_at_least(1), error);

            //if (error && error != asio::error::eof) {
                //spdlog::warn("receive failed {}", error.message());
            //}
            //const char* data = asio::buffer_cast<const char*>(receive_buffer.data());
            //spdlog::info(data);
        }
    }

    void Server::Stop(){
        this->sock.close();
    }
}