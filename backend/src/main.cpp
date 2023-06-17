#include <iostream>
#include <boost/asio.hpp>
#include <memory>

#include "./Server/Server.hpp"
#include "./Handler/TestHandler.hpp"

int main(){
    FruitsGroove::Server server{std::make_unique<FruitsGroove::TestHandler>()};

    server.Run();

    std::cout << "Hello Mosa cup!" << std::endl;
}
