#pragma once
#include <string>

namespace FruitsGroove{
    class HandlerBase{
    public:
        virtual void Handle(std::string) = 0;
    };
}

