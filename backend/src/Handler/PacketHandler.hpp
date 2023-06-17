#pragma once
#include "./HandlerBase.hpp"
#include "src/Protocol/Packet.hpp"
#include <string_view>
#include "src/Operation/OperationBase.hpp"
#include "src/Protocol/PacketParser.hpp"
#include <memory>

namespace FruitsGroove{
    class PacketHandler: public HandlerBase{
        std::vector<std::shared_ptr<OperationBase>> operationArray;
    public:
        void Handle(std::string_view rawData, Room& room) override{
            auto packet = ParsePacket(rawData);

            for(auto& op: this->operationArray){
                if(op->IsMyOperation(packet.op)){
                    op->Execute(rawData, room);
                }
            }

        };
    };
}