#pragma once
#include "Executor.hpp"
#include "PoseHandler.hpp"

namespace adas
{
class ExecutorImpl final : public Executor
{
public:
    explicit ExecutorImpl(const Pose& pose, VehicleType type = VehicleType::Normal) noexcept;
    ~ExecutorImpl() noexcept override = default;

    ExecutorImpl(const ExecutorImpl&) = delete;
    ExecutorImpl& operator=(const ExecutorImpl&) = delete;

public:
    void Execute(const std::string& commands) noexcept override;
    Pose Query(void) const noexcept override;

private:
    PoseHandler poseHandler;
};
}