#pragma once
#include "src/Protocol/OperationType.hpp"
#include "src/Protocol/Packet.hpp"
#include <string_view>
#include <boost/asio.hpp>

namespace asio = boost::asio;
using asio::ip::tcp;

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

    virtual void Execute(const Packet& packet, std::unique_ptr<tcp::socket>& socket) = 0;
};

}