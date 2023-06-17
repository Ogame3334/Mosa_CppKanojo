//#include <memory>
//#include <boost/asio.hpp>
//#include <array>

//namespace asio = boost::asio;
//using asio::ip::tcp;

//namespace FruitsGroove{
    //class Room{
        //std:
    //public:
        //Room(std::unique_ptr<tcp::socket>s1, std::unique_ptr<tcp::socket>s2){

        //}



    //};

//}

#pragma once
#include "src/Handler/PacketHandler.hpp"
#include <array>
#include <string_view>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include <thread>

namespace FruitsGroove{
class Room{
    using SocketPtr = std::unique_ptr<boost::asio::ip::tcp::socket>;
private:
    std::array<SocketPtr, 2> socketArray;
    std::array<std::thread, 2> threadArray;
    PacketHandler packetHandler{};
    // 二つの曲名
    void SocketDataProcessor(SocketPtr dest_socket, SocketPtr source_socket);
public:
    Room() = delete;
    Room(std::array<SocketPtr, 2>&& socketArray):
        socketArray(std::move(socketArray))
        {}
};
}
//ここまで

// namespace asio = boost::asio;
// using asio::ip::tcp;

// namespace FruitsGroove{
// class Room{
// private:
//     int roomID;
//     std::array<User, 2> userArray;
//     bool isEnded;
// public:
//     Room(int roomID, std::array<User, 2>&& userArray):
//         roomID(roomID),
//         userArray(std::move(userArray)),
//         isEnded{false}
//     {}
    
//     bool IsEnded() const{
//         return this->isEnded;
//     }

//     void SendMessageToOther(std::string_view userID, std::string_view payload){
//         tcp::socket* sock;
//         if(this->userArray.at(0).id == userID){
//             sock = &(this->userArray.at(1).socket);
//         }else{
//             sock = &(this->userArray.at(0).socket);
//         }
//         // メッセージ送信
//         boost::system::error_code error;
//         asio::write(*sock, asio::buffer(payload), error);
//         if(error){
//             spdlog::warn(__func__, ": ", "error");
//         }
//         spdlog::info(__func__, ": ", "send message ", payload, " to ", userID);
//     }
// };
// }
