#pragma once 
#include <thread>
#include <vector>
#include <memory>

namespace FruitsGroove{
    class HandlerProcessExecuter{
        std::vector<std::unique_ptr<std::thread>> threadArray;
    public:
        void AddTask(std::unique_ptr<std::thread> threadPtr){
            this->threadArray.emplace_back(std::move(threadPtr));
        }
    };
}