#pragma once
#include <string>
#include <string_view>

namespace FruitsGroove{
    class HandlerBase{
    public:
        virtual void Handle(std::string_view) = 0;
    };
}

