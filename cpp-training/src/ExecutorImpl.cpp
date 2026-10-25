#include "ExecutorImpl.hpp"
#include <memory>

namespace adas
{
ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : pose(pose)
{
}

// ===== 14页：把原来的大 if-else 抽成三个成员函数 =====
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

// ===== Execute 改为按字符遍历（支持多指令序列）=====
void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    for (const char cmd : commands)
    {
        if (cmd == 'M')
        {
            Move();
        }
        else if (cmd == 'L')
        {
            TurnLeft();
        }
        else if (cmd == 'R')
        {
            TurnRight();
        }
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
} // namespace adas

// 工厂函数保持不变
std::unique_ptr<Executor> Executor::NewExecutor(const Pose& init_pose)
{
    return std::make_unique<adas::ExecutorImpl>(init_pose);
}

std::unique_ptr<Executor> Executor::NewExecutor()
{
    Pose defaultPose{};
    defaultPose.x = 0.0;
    defaultPose.y = 0.0;
    defaultPose.heading = 78;   // ← 这里必须是 0（N）
    return std::make_unique<adas::ExecutorImpl>(defaultPose);
}