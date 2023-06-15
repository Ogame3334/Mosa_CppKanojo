#pragma once
#include "./HandlerBase.hpp"
#include <string_view>

namespace FruitsGroove{
    class PacketHandler: public HandlerBase{
    public:
        void Handle(std::string_view data) override{
            
        };
    };
}