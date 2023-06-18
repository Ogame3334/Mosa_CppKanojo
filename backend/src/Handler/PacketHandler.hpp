#pragma once
#include "./HandlerBase.hpp"
#include "src/Protocol/Packet.hpp"
#include <string_view>
#include "src/Operation/OperationBase.hpp"
#include "src/Protocol/PacketParser.hpp"
#include <memory>

namespace FruitsGroove{
    class PacketHandler: public HandlerBase{
        std::vector<std::unique_ptr<OperationBase>> operationArray;
    public:
        void Handle(Packet packet, std::unique_ptr<tcp::socket>& socket, Room& room) override{
            for(auto& op: this->operationArray){
                if(packet.op == op->GetOperationType()){
                    op->Execute(packet, socket, room);
                }
            }
        };
        void AddOperation(std::unique_ptr<OperationBase>&& sp){
            this->operationArray.emplace_back(std::move(sp));
        }
    };
}