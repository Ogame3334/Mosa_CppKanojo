#pragma once
#include "src/Room/Room.hpp"
#include <memory>
#include <vector>
#include <spdlog/spdlog.h>

namespace FruitsGroove{
class RoomManager{
private:
    using RoomPtrArray = std::vector<std::shared_ptr<Room>>;
    int latestRoomIndex = 0;
    RoomPtrArray roomArray;
public:
    void CleanUpRoom(){
        for(auto& roomPtr: this->roomArray){
            if(roomPtr->IsEnded()){
                roomPtr = nullptr;
            }
        }
    }

    auto FindEndedRoom(){
        this->CleanUpRoom();
        for(auto&& itr = this->roomArray.begin(); itr != this->roomArray.end(); itr++){
            if(*itr == nullptr){
                return itr;
            }
        }
        return this->roomArray.end();
    }

    void CreateRoom(std::array<User, 2>&& userArray){
        auto endedRoomItr = this->FindEndedRoom();
        (*endedRoomItr).reset(new Room{this->latestRoomIndex++, std::move(userArray)});
        spdlog::info("room created");
    }

};
}