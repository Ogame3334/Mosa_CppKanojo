#pragma once
#include "src/Protocol/OperationType.hpp"
#include <string_view>

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

    virtual void Execute(std::string_view) = 0;
};

}