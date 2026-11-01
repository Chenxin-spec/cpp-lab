#include "ExecutorImpl.hpp"
#include "Command.hpp"
#include <unordered_map>
#include <functional>

namespace adas
{
ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : poseHandler(pose)
{
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    // 函数式 + 表驱动
    static const std::unordered_map<char, std::function<void(PoseHandler&)>> cmderMap = {
        {'M', MoveCommand{}},
        {'L', TurnLeftCommand{}},
        {'R', TurnRightCommand{}},
        {'F', FastCommand{}}
    };

    for (const auto cmd : commands)
    {
        const auto it = cmderMap.find(cmd);
        if (it != cmderMap.end())
        {
            it->second(poseHandler);   // 直接调用
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
