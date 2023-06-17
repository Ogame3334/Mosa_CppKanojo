#pragma once
#include "src/Protocol/OperationType.hpp"
#include <string_view>
#include <memory>
#include "src/Protocol/Packet.hpp"
#include <boost/asio.hpp>
#include "src/Room/Room.hpp"

namespace FruitsGroove{

class OperationBase{
    OperationType opType;
public:
    OperationBase(OperationType op):
        opType(op)
    {}

    OperationType GetOperationType() const{
        return this->opType;
    }

    virtual void Execute(Packet packet, std::unique_ptr<boost::asio::ip::tcp::socket>& socket, Room& room) = 0;
};

}