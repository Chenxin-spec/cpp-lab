// src/Command.cpp
#include "Command.hpp"
#include "PoseHandler.hpp"

namespace adas
{

void MoveCommand::DoOperate(PoseHandler& ph) const noexcept
{
    if (ph.IsFast())
    {
        ph.Move();
    }
    ph.Move();
}

void TurnLeftCommand::DoOperate(PoseHandler& ph) const noexcept
{
    if (ph.IsFast())
    {
        ph.Move();
    }
    ph.TurnLeft();
}

void TurnRightCommand::DoOperate(PoseHandler& ph) const noexcept
{
    if (ph.IsFast())
    {
        ph.Move();
    }
    ph.TurnRight();
}

void FastCommand::DoOperate(PoseHandler& ph) const noexcept
{
    ph.Fast();
}

} // namespace adas