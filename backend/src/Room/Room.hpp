#pragma once
#include <array>
#include <string_view>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include "src/User/User.hpp"

namespace FruitsGroove{
class Room{
    using SocketPtr = std::unique_ptr<boost::asio::ip::tcp::socket>;
private:
    int roomID;
    std::array<User, 2> userArray;
public:
    Room() = delete;
    Room(int roomID, std::array<SocketPtr, 2> sockets);
};
}


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
