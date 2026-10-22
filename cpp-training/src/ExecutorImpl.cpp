#include "ExecutorImpl.hpp"
#include <memory>

namespace adas
{
ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : pose(pose)
{
}

void ExecutorImpl::Execute(const std::string& command) noexcept
{
}

Pose ExecutorImpl::Query(void) const noexcept
{
    return pose;
}
} // namespace adas

// ✅ 注意：加上 Executor:: 和头文件static声明对应！
std::unique_ptr<Executor> Executor::NewExecutor(const Pose& init_pose)
{
    return std::make_unique<adas::ExecutorImpl>(init_pose);
}

std::unique_ptr<Executor> Executor::NewExecutor()
{
    Pose defaultPose{};
    defaultPose.x = 0.0;
    defaultPose.y = 0.0;
    defaultPose.heading = 78.0;
    return std::make_unique<adas::ExecutorImpl>(defaultPose);
}
