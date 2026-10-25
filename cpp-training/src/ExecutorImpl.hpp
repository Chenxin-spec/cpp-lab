#pragma once
#include "Executor.hpp"
#include <memory>
#include <string>

namespace adas
{
class ExecutorImpl final : public Executor
{
public:
    explicit ExecutorImpl(const Pose& pose) noexcept;
    void Execute(const std::string& commands) noexcept override;
    Pose Query() const noexcept override;

private:
    void Move() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;
    void Fast() noexcept;
    bool IsFast() const noexcept;

    class ICommand
    {
    public:
        virtual ~ICommand() = default;
        virtual void DoOperate(ExecutorImpl& executor) const noexcept = 0;
    };

    class MoveCommand final : public ICommand
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept override
        {
            if (executor.IsFast())
            {
                executor.Move();
            }
            executor.Move();
        }
    };

    class TurnLeftCommand final : public ICommand
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept override
        {
            if (executor.IsFast())
            {
                executor.Move();
            }
            executor.TurnLeft();
        }
    };

    class TurnRightCommand final : public ICommand
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept override
        {
            if (executor.IsFast())
            {
                executor.Move();
            }
            executor.TurnRight();
        }
    };

    class FastCommand final : public ICommand
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept override
        {
            executor.Fast();
        }
    };

    Pose pose;
    bool fast{false};
};
} // namespace adas