#pragma once
#include "OperationType.hpp"

namespace FruitsGroove{
struct Packet{
    OperationType op;
    std::string content;

};
}
