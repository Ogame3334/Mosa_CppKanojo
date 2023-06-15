#pragma once

#include <memory>
#include "../Handler/HandlerBase.hpp"

namespace FruitsGroove{
    class Server{
        using HandlerPtr = std::unique_ptr<HandlerBase>;
    private:
        HandlerPtr handerInstance;
    public:
        Server() = default;
        Server(HandlerPtr instance);
        void Start();
        void Stop();
    };
}