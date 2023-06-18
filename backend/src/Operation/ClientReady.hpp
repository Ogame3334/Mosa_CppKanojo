#pragma once
#include "OperationBase.hpp"
#include "src/Protocol/PacketBuilder.hpp"
#include <mutex>

inline std::mutex playerCountMtx;
inline int readyPlayerCount = 0;

namespace FruitsGroove{
class ClientReady: public OperationBase{
    public:
    ClientReady():
        OperationBase(OperationType::ClientReady)
    {}

    void Execute(const Packet& packet, std::unique_ptr<tcp::socket>& socket) override{
        {
            std::lock_guard<std::mutex> lock(playerCountMtx);
            readyPlayerCount += 1;
        }
        while(readyPlayerCount < 2){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        boost::system::error_code error;
        asio::write(*socket, asio::buffer("10"), error);
    }
};
}