// src/PoseHandler.hpp
#pragma once

#include "Executor.hpp"

namespace adas
{

class PoseHandler final
{
public:
    explicit PoseHandler(const Pose& pose) noexcept;

    PoseHandler(const PoseHandler&) = delete;
    PoseHandler& operator=(const PoseHandler&) = delete;

    void Move() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;
    void Fast() noexcept;
    bool IsFast() const noexcept;
    Pose Query() const noexcept;
    void Reverse() noexcept;
    bool IsReverse() const noexcept;
    void Forward() noexcept;
    void Backward() noexcept;
    void TurnLeftImpl() noexcept;
    void TurnRightImpl() noexcept;
private:
    Pose pose;
    bool fast{false};
    bool reverse{false};
    // PoseHandler.hpp 的 private 区域增加
};

} // namespace adas