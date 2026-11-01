#include "ExecutorImpl.hpp"
#include "Command.hpp"

namespace adas
{
ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : poseHandler(pose)
{
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    // 本步骤暂时保留if‑else，下一个步骤改成表驱动
    for (auto c : commands)
    {
        std::unique_ptr<ICommand> cmd;
        if (c == 'M')
        {
            cmd = std::make_unique<MoveCommand>();
        }
        else if (c == 'L')
        {
            cmd = std::make_unique<TurnLeftCommand>();
        }
        else if (c == 'R')
        {
            cmd = std::make_unique<TurnRightCommand>();
        }
        else if (c == 'F')
        {
            cmd = std::make_unique<FastCommand>();
        }

        if (cmd)
        {
            cmd->DoOperate(poseHandler);
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
