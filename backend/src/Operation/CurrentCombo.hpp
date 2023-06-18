#pragma once
#include "OperationBase.hpp"
#include "src/Protocol/PacketBuilder.hpp"

namespace FruitsGroove{
class CurrentCombo: public OperationBase{
    public:
    CurrentCombo():
        OperationBase(OperationType::CurrentCombo)
    {}

    void Execute(const Packet& packet, std::unique_ptr<tcp::socket>& socket) override{
        PacketBuilder pb;
        auto payload = pb.SetOperation(packet.op).SetContent(packet.content).Build();
        boost::system::error_code error;
        asio::write(*socket, asio::buffer(payload), error);
    }
};
}