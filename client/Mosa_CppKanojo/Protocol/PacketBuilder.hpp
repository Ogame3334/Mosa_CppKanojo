#pragma once
#include "OperationType.hpp"
#include <string_view>
#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>

namespace FruitsGroove{
class PacketBuilder{
private:
    OperationType opType;
    std::string content;
    
public:
    PacketBuilder(){};

    PacketBuilder& SetOperation(OperationType op){
        this->opType = op;
        return *this;
    }

    PacketBuilder& SetEtcString(std::string_view str){
        this->content = str;
        return *this;
    }

    std::string Build(){
        std::stringstream packetStringStream{""};
        
        auto operationTypeNum = static_cast<int>(this->opType);
        if(operationTypeNum > 99){
            throw std::logic_error{"operationは99を超えないはずです"};
        }

        packetStringStream << std::setw(2) << std::setfill('0') << operationTypeNum;

        packetStringStream << this->content;
    }
};
}