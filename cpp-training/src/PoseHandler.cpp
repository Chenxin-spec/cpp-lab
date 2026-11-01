// src/PoseHandler.cpp
#include "PoseHandler.hpp"

namespace adas
{

PoseHandler::PoseHandler(const Pose& pose) noexcept : pose(pose)
{
}

void PoseHandler::Move() noexcept
{
    int dx = 0;
    int dy = 0;

    if (pose.heading == 69)       // E
        dx = 1;
    else if (pose.heading == 249) // W
        dx = -1;
    else if (pose.heading == 0)   // N
        dy = 1;
    else if (pose.heading == 159) // S
        dy = -1;

    // 倒车时方向取反
    if (IsReverse())
    {
        dx = -dx;
        dy = -dy;
    }

    pose.x += dx;
    pose.y += dy;
}

void PoseHandler::TurnLeft() noexcept
{
    if (IsReverse())
    {
        // 倒车时 L 变成原来的 R
        TurnRightImpl();
    }
    else
    {
        TurnLeftImpl();
    }
}

void PoseHandler::TurnRight() noexcept
{
    if (IsReverse())
    {
        // 倒车时 R 变成原来的 L
        TurnLeftImpl();
    }
    else
    {
        TurnRightImpl();
    }
}

void PoseHandler::Fast() noexcept
{
    fast = !fast;
}

bool PoseHandler::IsFast() const noexcept
{
    return fast;
}

Pose PoseHandler::Query() const noexcept
{
    return pose;
}

void PoseHandler::Reverse() noexcept
{
    reverse = !reverse;
}

bool PoseHandler::IsReverse() const noexcept
{
    return reverse;
}

// PoseHandler.cpp
void PoseHandler::TurnLeftImpl() noexcept
{
    if (pose.heading == 69)        // E → N
        pose.heading = 0;
    else if (pose.heading == 0)    // N → W
        pose.heading = 249;
    else if (pose.heading == 249)  // W → S
        pose.heading = 159;
    else if (pose.heading == 159)  // S → E
        pose.heading = 69;
}

void PoseHandler::TurnRightImpl() noexcept
{
    if (pose.heading == 69)        // E → S
        pose.heading = 159;
    else if (pose.heading == 159)  // S → W
        pose.heading = 249;
    else if (pose.heading == 249)  // W → N
        pose.heading = 0;
    else if (pose.heading == 0)    // N → E
        pose.heading = 69;
}

} // namespace adas
