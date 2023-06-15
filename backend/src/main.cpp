#include <iostream>
#include <boost/asio.hpp>

#include "./Server/Server.hpp"

int main(){
    FruitsGroove::Server server{};

    server.Start();

    std::cout << "Hello Mosa cup!" << std::endl;
}
