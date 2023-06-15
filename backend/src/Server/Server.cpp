#include "Server.hpp"

namespace FruitsGroove{
    Server::Server(HandlerPtr instance){
        this->handerInstance = std::move(instance);
    }

    void Server::Start(){
        for(;;){ // <-可愛い！！！！
            
        }
    }

    void Server::Stop(){

    }
}