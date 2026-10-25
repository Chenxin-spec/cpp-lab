#include "ExecutorImpl.hpp"
#include <memory>

namespace adas
{
ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : pose(pose)
{
}

void ExecutorImpl::Move() noexcept
{
    if (pose.heading == 0)          // N
    {
        pose.y = pose.y + 1;
    }
    else if (pose.heading == 69)    // E
    {
        pose.x = pose.x + 1;
    }
    else if (pose.heading == 159)   // S
    {
        pose.y = pose.y - 1;
    }
    else if (pose.heading == 249)   // W
    {
        pose.x = pose.x - 1;
    }
}

void ExecutorImpl::TurnLeft() noexcept
{
    if (pose.heading == 0)          pose.heading = 249;   // N -> W
    else if (pose.heading == 69)    pose.heading = 0;     // E -> N
    else if (pose.heading == 159)   pose.heading = 69;    // S -> E
    else if (pose.heading == 249)   pose.heading = 159;   // W -> S
}

void ExecutorImpl::TurnRight() noexcept
{
    if (pose.heading == 0)          pose.heading = 69;    // N -> E
    else if (pose.heading == 69)    pose.heading = 159;   // E -> S
    else if (pose.heading == 159)   pose.heading = 249;   // S -> W
    else if (pose.heading == 249)   pose.heading = 0;     // W -> N
}

void ExecutorImpl::Fast() noexcept
{
    fast = !fast;
}

bool ExecutorImpl::IsFast() const noexcept
{
    return fast;
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    for (const char cmd : commands)
    {
        std::unique_ptr<ICommand> cmder;
        if (cmd == 'M')
        {
            cmder = std::make_unique<MoveCommand>();
        }
        else if (cmd == 'L')
        {
            cmder = std::make_unique<TurnLeftCommand>();
        }
        else if (cmd == 'R')
        {
            cmder = std::make_unique<TurnRightCommand>();
        }
        else if (cmd == 'F')
        {
            cmder = std::make_unique<FastCommand>();
        }

        if (cmder)
        {
            cmder->DoOperate(*this);
        }
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
} // namespace adas

// 工厂函数
std::unique_ptr<Executor> Executor::NewExecutor(const Pose& init_pose)
{
    return std::make_unique<adas::ExecutorImpl>(init_pose);
}

std::unique_ptr<Executor> Executor::NewExecutor()
{
    Pose defaultPose{};
    defaultPose.x = 0.0;
    defaultPose.y = 0.0;
    defaultPose.heading = 78;
    return std::make_unique<adas::ExecutorImpl>(defaultPose);
}