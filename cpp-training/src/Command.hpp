#pragma once

#include "PoseHandler.hpp"
#include "ActionGroup.hpp"

namespace adas
{

class MoveCommand final
{
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        ActionGroup actionGroup;
        const auto type = poseHandler.GetVehicleType();
        const bool isReverse = poseHandler.IsReverse();
        const bool isFast = poseHandler.IsFast();

        ActionType step = isReverse ? ActionType::BACKWARD_1_STEP_ACTION
                                    : ActionType::FORWARD_1_STEP_ACTION;

        if (type == VehicleType::SportsCar)
        {
            // 跑车：一次移动 2 格（加速时 4 格）
            int times = isFast ? 4 : 2;
            for (int i = 0; i < times; ++i)
                actionGroup.PushAction(step);
        }
        else if (type == VehicleType::Bus)
        {
            // 公交车：一次移动 1 格（加速时 2 格）
            int times = isFast ? 2 : 1;
            for (int i = 0; i < times; ++i)
                actionGroup.PushAction(step);
        }
        else
        {
            // 普通车：原来的逻辑
            if (isFast) actionGroup.PushAction(step);
            actionGroup.PushAction(step);
        }

        return actionGroup;
    }
};

class TurnLeftCommand final
{
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        ActionGroup actionGroup;
        const auto type = poseHandler.GetVehicleType();
        const bool isReverse = poseHandler.IsReverse();
        const bool isFast = poseHandler.IsFast();

        ActionType moveAction = isReverse ? ActionType::BACKWARD_1_STEP_ACTION
                                          : ActionType::FORWARD_1_STEP_ACTION;
        ActionType turnAction = isReverse ? ActionType::REVERSE_TURNLEFT_ACTION
                                          : ActionType::TURNLEFT_ACTION;

        if (type == VehicleType::Bus)
        {
            // Bus: 先移动，再转向
            int moveTimes = isFast ? 2 : 1;
            for (int i = 0; i < moveTimes; ++i)
                actionGroup.PushAction(moveAction);
            actionGroup.PushAction(turnAction);
        }
        else if (type == VehicleType::SportsCar)
        {
            // 跑车: 先转向，再移动
            actionGroup.PushAction(turnAction);
            int moveTimes = isFast ? 2 : 1;
            for (int i = 0; i < moveTimes; ++i)
                actionGroup.PushAction(moveAction);
        }
        else
        {
            // 普通车: 原来的逻辑（加速时先移动再转向）
            if (isFast)
                actionGroup.PushAction(moveAction);
            actionGroup.PushAction(turnAction);
        }

        return actionGroup;
    }
};

class TurnRightCommand final
{
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        ActionGroup actionGroup;
        const auto type = poseHandler.GetVehicleType();
        const bool isReverse = poseHandler.IsReverse();
        const bool isFast = poseHandler.IsFast();

        ActionType moveAction = isReverse ? ActionType::BACKWARD_1_STEP_ACTION
                                          : ActionType::FORWARD_1_STEP_ACTION;
        ActionType turnAction = isReverse ? ActionType::REVERSE_TURNRIGHT_ACTION
                                          : ActionType::TURNRIGHT_ACTION;

        if (type == VehicleType::Bus)
        {
            // Bus: 先移动，再转向
            int moveTimes = isFast ? 2 : 1;
            for (int i = 0; i < moveTimes; ++i)
                actionGroup.PushAction(moveAction);
            actionGroup.PushAction(turnAction);
        }
        else if (type == VehicleType::SportsCar)
        {
            // 跑车: 先转向，再移动
            actionGroup.PushAction(turnAction);
            int moveTimes = isFast ? 2 : 1;
            for (int i = 0; i < moveTimes; ++i)
                actionGroup.PushAction(moveAction);
        }
        else
        {
            // 普通车: 原来的逻辑
            if (isFast)
                actionGroup.PushAction(moveAction);
            actionGroup.PushAction(turnAction);
        }

        return actionGroup;
    }
};

class FastCommand final
{
public:
    ActionGroup operator()(PoseHandler& /*poseHandler*/) const noexcept
    {
        ActionGroup actionGroup;
        actionGroup.PushAction(ActionType::BE_FAST_ACTION);
        return actionGroup;
    }
};

class ReverseCommand final
{
public:
    ActionGroup operator()(PoseHandler& /*poseHandler*/) const noexcept
    {
        ActionGroup actionGroup;
        actionGroup.PushAction(ActionType::BE_REVERSE_ACTION);
        return actionGroup;
    }
};

class TurnRoundCommand final
{
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        // 倒车状态下忽略 TR
        if (poseHandler.IsReverse())
        {
            return ActionGroup{};
        }

        if (poseHandler.IsFast())
        {
            // 加速：前进 → 左转 → 前进 → 左转
            return ActionGroup{
                ActionType::FORWARD_1_STEP_ACTION,
                ActionType::TURNLEFT_ACTION,
                ActionType::FORWARD_1_STEP_ACTION,
                ActionType::TURNLEFT_ACTION
            };
        }

        // 普通：左转 → 前进 → 左转
        return ActionGroup{
            ActionType::TURNLEFT_ACTION,
            ActionType::FORWARD_1_STEP_ACTION,
            ActionType::TURNLEFT_ACTION
        };
    }
};

} // namespace adas