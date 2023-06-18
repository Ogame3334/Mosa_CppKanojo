#pragma once
#include "OperationBase.hpp"
#include "src/Protocol/PacketBuilder.hpp"
#include <mutex>

inline std::mutex playerCountMtx2;
inline int readyPlayerCount2 = 0;

namespace FruitsGroove{
class GameEnd: public OperationBase{
    public:
    GameEnd():
        OperationBase(OperationType::GameEnd)
    {}

    void Execute(const Packet& packet, std::unique_ptr<tcp::socket>& socket, Room& room) override{
        {
            std::lock_guard<std::mutex> lock(playerCountMtx2);
            readyPlayerCount2 += 1;
        }
        while(readyPlayerCount2 < 2){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        PacketBuilder pb;
        auto payload = pb.SetContent(packet.content).SetOperation(OperationType::ResultScore).Build();
        boost::system::error_code error;
        asio::write(*socket, asio::buffer(payload), error);
    }
};
}
