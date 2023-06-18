#include <iostream>
#include <boost/asio.hpp>
#include <memory>

#include "./Server/Server.hpp"

int main(){
    FruitsGroove::Server server{std::make_unique<FruitsGroove::PacketHandler>()};

    server.Run();

    std::cout << "Hello Mosa cup!" << std::endl;
}
