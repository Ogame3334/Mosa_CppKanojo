#pragma once
#include <string>
#include <string_view>
#include <boost/asio.hpp>
#include <memory>
class Room; //TODO #include "src/Room/Room.h" 実装時に置き換え


namespace FruitsGroove{
    class HandlerBase{
    public:
    virtual void Handle(std::string_view, Room&) = 0;
    };
}

