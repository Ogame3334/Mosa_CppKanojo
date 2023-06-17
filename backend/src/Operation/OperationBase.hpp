#pragma once
#include "src/Protocol/OperationType.hpp"
#include <string_view>

namespace FruitsGroove{

class OperationBase{
protected:
    OperationType opType;
public:
    OperationBase(OperationType op):
        opType(op)
    {}

    [[deprecated]]
    OperationType GetOperationType() const{
        return this->opType;
    }

    virtual bool IsMyOperation(OperationType)const = 0;
    virtual void Execute(std::string_view) = 0;
};

}