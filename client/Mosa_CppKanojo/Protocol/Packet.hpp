#pragma once
#include "OperationType.hpp"
#include <string>

namespace FruitsGroove{
struct Packet{
    OperationType op;
    std::string content;

};
}
