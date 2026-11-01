#include "ExecutorImpl.hpp"
#include "Command.hpp"
#include <unordered_map>

namespace adas
{
ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : poseHandler(pose)
{
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    // 表驱动
    static const std::unordered_map<char, std::unique_ptr<ICommand>> cmderMap = []() {
        std::unordered_map<char, std::unique_ptr<ICommand>> map;
        map.emplace('M', std::make_unique<MoveCommand>());
        map.emplace('L', std::make_unique<TurnLeftCommand>());
        map.emplace('R', std::make_unique<TurnRightCommand>());
        map.emplace('F', std::make_unique<FastCommand>());
        return map;
    }();

    for (const auto cmd : commands)
    {
        const auto it = cmderMap.find(cmd);
        if (it != cmderMap.end())
        {
            it->second->DoOperate(poseHandler);
        }
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return poseHandler.Query();
}
}

std::unique_ptr<Executor> Executor::NewExecutor(const Pose& init_pose)
{
    return std::make_unique<adas::ExecutorImpl>(init_pose);
}

std::unique_ptr<Executor> Executor::NewExecutor()
{
    return std::make_unique<adas::ExecutorImpl>(Pose{0, 0, 78});
}
