#pragma once
#include "OperationBase.hpp"
#include "src/Protocol/PacketBuilder.hpp"
#include <mutex>
#include <vector>
#include <thread>
#include <spdlog/spdlog.h>

inline std::mutex songNameArraymtx;
inline std::vector<std::string> songNameArray;

namespace FruitsGroove{
class SelectSong: public OperationBase{
    public:
    SelectSong():
        OperationBase(OperationType::SelectedSong)
    {}

    void Execute(const Packet& packet, std::unique_ptr<tcp::socket>& socket) override{
        spdlog::info("select song");
        {
            std::lock_guard<std::mutex> lock(songNameArraymtx);
            songNameArray.emplace_back(packet.content);
            boost::system::error_code error;
            asio::write(*socket, asio::buffer("07"), error);
        }
        while(songNameArray.size() < 2){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        //TODO shuffle
            boost::system::error_code error;
        asio::write(*socket, asio::buffer("08" + songNameArray[0]), error);
    }
};
}