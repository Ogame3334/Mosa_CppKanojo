#pragma once
#include "src/Protocol/OperationType.hpp"
#include <string_view>
class Room; //TODO #include "src/Room/Room.h" 実装時に置き換え

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
    virtual void Execute(std::string_view, Room&) = 0;
};

}