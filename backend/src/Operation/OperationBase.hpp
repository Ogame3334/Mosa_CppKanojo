#pragma once
#include "src/Protocol/OperationType.hpp"
#include <string_view>
#include "src/Protocol/Packet.hpp"

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

    virtual void Execute(Packet packet) = 0;
};

}