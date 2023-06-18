#include "src/Room/RoomManager.hpp"

#include "src/Operation/ClientReady.hpp"
#include "src/Operation/CurrentCombo.hpp"
#include "src/Operation/CurrentScore.hpp"
#include "src/Operation/GameEnd.hpp"
#include "src/Operation/NoticeIDAndName.hpp"
#include "src/Operation/SelectSong.hpp"

namespace FruitsGroove{
    RoomManager::RoomManager(){
        this->packetHandler.AddOperation(std::make_unique<ClientReady>());
        this->packetHandler.AddOperation(std::make_unique<CurrentCombo>());
        this->packetHandler.AddOperation(std::make_unique<CurrentScore>());
        this->packetHandler.AddOperation(std::make_unique<GameEnd>());
        this->packetHandler.AddOperation(std::make_unique<NoticeIDAndName>());
        this->packetHandler.AddOperation(std::make_unique<SelectSong>());
    }

    void RoomManager::createRoom(SocketPtr socket1, SocketPtr socket2){
        this->rooms.emplace_back(std::make_unique<Room>( std::array<SocketPtr, 2>{ std::move(socket1), std::move(socket2) } ));
    }
}