#include "./PacketBuilder.hpp"
#include <stdexcept>
#include <sstream>
#include <iomanip>

namespace FruitsGroove{
    PacketBuilder& PacketBuilder::SetOperation(OperationType op){
        this->opType = op;
        return *this;
    }

    PacketBuilder& PacketBuilder::SetContent(std::string_view str){
        this->content = str;
        return *this;
    }

    std::string PacketBuilder::Build(){
        std::stringstream packetStringStream{};
        
        auto operationTypeNum = static_cast<int>(this->opType);
        if(operationTypeNum > 99){
            throw std::logic_error{"operationは99を超えないはずです"};
        }

        packetStringStream << std::setw(2) << std::setfill('0') << operationTypeNum;

        packetStringStream << this->content;
        return packetStringStream.str();
    }
}
