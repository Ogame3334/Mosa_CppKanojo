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
    PacketBuilder();

    PacketBuilder& SetOperation(OperationType op);

    PacketBuilder& SetContent(std::string_view str);

    std::string Build();
};
}