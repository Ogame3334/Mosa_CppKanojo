#pragma once
#include "./HandlerBase.hpp"
#include "src/Protocol/Packet.hpp"
#include <string_view>
#include "src/Operation/OperationBase.hpp"
#include "src/Protocol/PacketParser.hpp"
#include <memory>

namespace FruitsGroove{
    class PacketHandler: public HandlerBase{
        std::vector<OperationBase*> operationArray;
    public:
        void Handle(std::string_view rawData) override{
            auto packet = ParsePacket(rawData);

            for(auto& op: this->operationArray){
                if(packet.op == op->GetOperationType()){
                    op->Execute(rawData);
                }
            }

        };
    };
}