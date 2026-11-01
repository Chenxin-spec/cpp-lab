// src/PoseHandler.cpp
#include "PoseHandler.hpp"

namespace adas
{

PoseHandler::PoseHandler(const Pose& pose) noexcept : pose(pose)
{
}

void PoseHandler::Move() noexcept
{
    if (pose.heading == 69)        // E
    {
        ++pose.x;
    }
    else if (pose.heading == 249)  // W
    {
        --pose.x;
    }
    else if (pose.heading == 0)    // N
    {
        ++pose.y;
    }
    else if (pose.heading == 159)  // S
    {
        --pose.y;
    }
}

void PoseHandler::TurnLeft() noexcept
{
    if (pose.heading == 69)        // E → N
    {
        pose.heading = 0;
    }
    else if (pose.heading == 0)    // N → W
    {
        pose.heading = 249;
    }
    else if (pose.heading == 249)  // W → S
    {
        pose.heading = 159;
    }
    else if (pose.heading == 159)  // S → E
    {
        pose.heading = 69;
    }
}

void PoseHandler::TurnRight() noexcept
{
    if (pose.heading == 69)        // E → S
    {
        pose.heading = 159;
    }
    else if (pose.heading == 159)  // S → W
    {
        pose.heading = 249;
    }
    else if (pose.heading == 249)  // W → N
    {
        pose.heading = 0;
    }
    else if (pose.heading == 0)    // N → E
    {
        pose.heading = 69;
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

} // namespace adas