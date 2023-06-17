#include "Server.hpp"
#include "src/Handler/HandlerProcessExecuter.hpp"
#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <spdlog/spdlog.h>
#include <thread>

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

            handlerExecuter.AddTask(std::make_unique<std::thread>(
                [&](){
                }
            ));

            std::this_thread::sleep_for(std::chrono::seconds(1));

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