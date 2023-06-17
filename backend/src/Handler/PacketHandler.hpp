#pragma once
#include "./HandlerBase.hpp"
#include "src/Protocol/Packet.hpp"
#include <string_view>
#include "src/Operation/OperationBase.hpp"
#include "src/Protocol/PacketParser.hpp"
#include <memory>
#include <spdlog/spdlog.h>

namespace FruitsGroove{
    class PacketHandler: public HandlerBase{
        std::vector<std::shared_ptr<OperationBase>> operationArray;
    public:
    void AddOperation(std::shared_ptr<OperationBase>&& sp){
        this->operationArray.emplace_back(std::move(sp));
    }

    void Handle(const Packet& packet, std::unique_ptr<tcp::socket>& sock){
        spdlog::info(packet.content);
            for(auto& op: this->operationArray){
                if(packet.op == op->GetOperationType()){
                    op->Execute(packet, sock);
                }
            }
        };
    };
}