#include "ExecutorImpl.hpp"
#include "Command.hpp"
#include <unordered_map>
#include <functional>
#include "CmderFactory.hpp"
#include "Singleton.hpp"
#include <algorithm>

namespace adas
{
ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : poseHandler(pose)
{
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    const auto cmders = Singleton<CmderFactory>::Instance().GetCmders(commands);

    std::for_each(cmders.begin(), cmders.end(),
                  [this](const Cmder& cmder) noexcept {
                      cmder(poseHandler);
                  });
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
