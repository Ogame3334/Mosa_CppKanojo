#pragma once
#include "HandlerBase.hpp"
#include <iostream>
#include <ostream>

namespace FruitsGroove{
class TestHandler: public HandlerBase{
    std::ostream& os;
    public:
    TestHandler(std::ostream& os):
        os(os)
    {}

    TestHandler():
        os(std::cout)
    {}

    void Handle(std::string_view data) override{
        this->os << data;
    }
};
}