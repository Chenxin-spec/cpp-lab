#pragma once
#include "Executor.hpp"
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
    // ===== 14页：函数抽取 =====
    void Move() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;

    Pose pose;
};
} // namespace adas