#include <iostream>
#include <boost/asio.hpp>
#include <memory>

#include "src/Server/Server.hpp"
#include "src/Handler/TestHandler.hpp"
#include "src/Handler/PacketHandler.hpp"

int main(){
    FruitsGroove::Server server{std::make_unique<FruitsGroove::PacketHandler>()};

    server.Start();

    std::cout << "Hello Mosa cup!" << std::endl;
}
