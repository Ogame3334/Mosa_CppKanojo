#pragma once
#include "OperationBase.hpp"
#include "src/Protocol/PacketBuilder.hpp"
#include <mutex>
#include <vector>
#include <thread>
#include <spdlog/spdlog.h>
#include <algorithm>


namespace FruitsGroove{
    inline std::mutex songNameArraymtx;
    
class SelectSong: public OperationBase{
    public:
    SelectSong():
        OperationBase(OperationType::SelectedSong)
    {}

    void Execute(const Packet& packet, std::unique_ptr<tcp::socket>& socket, Room& room) override{
        spdlog::info("select song");
        {
            std::lock_guard<std::mutex> lock(songNameArraymtx);
            room.songsArray.emplace_back(packet.content);
            boost::system::error_code error;
            asio::write(*socket, asio::buffer("07"), error);
        }
        while(room.songsArray.size() < 2){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::random_shuffle(room.songsArray.begin(), room.songsArray.end()); //TODO shuffle 多分できた
        boost::system::error_code error;
        asio::write(*socket, asio::buffer("08" + room.songsArray[0]), error);
    }
};
}