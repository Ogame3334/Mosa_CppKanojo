#pragma once
#include "OperationBase.hpp"
#include "src/Protocol/PacketBuilder.hpp"

namespace FruitsGroove{
class NoticeIDAndName: public OperationBase{
    public:
    NoticeIDAndName():
        OperationBase(OperationType::NoticeIDAndName)
    {}

    void Execute(const Packet& packet, std::unique_ptr<tcp::socket>& socket, Room& room) override{
        PacketBuilder pb;
        auto payload = pb.SetOperation(packet.op).SetContent(packet.content).Build();
        boost::system::error_code error;
        asio::write(*socket, asio::buffer(payload), error);
    }
};
}