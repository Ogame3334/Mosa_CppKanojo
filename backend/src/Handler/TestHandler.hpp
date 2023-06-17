//#pragma once
//#include "HandlerBase.hpp"
//#include <iostream>
//#include <ostream>
//#include <spdlog/spdlog.h>

//namespace asio = boost::asio;
//using boost::asio::ip::tcp;

//namespace FruitsGroove{
//class TestHandler: public HandlerBase{
    //std::ostream& os;
    //public:
    //TestHandler(std::ostream& os):
        //os(os)
    //{}

    //TestHandler():
        //os(std::cout)
    //{}

    //void Handle(std::string_view) override{
        ////while(true){
            ////boost::system::error_code error;
            ////asio::streambuf receive_buffer;
            ////spdlog::info("handle: socket read start");
            ////asio::read(*socket, receive_buffer, asio::transfer_at_least(1), error);
            ////if(!socket->available()) spdlog::warn("socket is not available", error.message());
            ////if(!socket->is_open()) spdlog::warn("socket is not opened", error.message());

            ////if (error && error != asio::error::eof) {
                ////spdlog::warn("receive failed: {}", error.message());
                ////return;
            ////}
            ////const char* data = asio::buffer_cast<const char*>(receive_buffer.data());
            ////spdlog::info(data);
        ////}
    //}
//};
//}