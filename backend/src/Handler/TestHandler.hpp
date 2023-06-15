#pragma once
#include "HandlerBase.hpp"
#include <iostream>

namespace FruitsGroove{
class TestHandler: public HandlerBase{
    public:
    TestHandler() {}
    void Handle(std::string_view data) override{
        std::cout << data << std::endl;
    }
};
}