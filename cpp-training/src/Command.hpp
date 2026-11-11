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

        const ActionType action = poseHandler.IsReverse()
                                      ? ActionType::BACKWARD_1_STEP_ACTION
                                      : ActionType::FORWARD_1_STEP_ACTION;

        if (poseHandler.IsFast())
        {
            actionGroup.PushAction(action);
        }
        actionGroup.PushAction(action);

        return actionGroup;
    }
};

class TurnLeftCommand final
{
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        ActionGroup actionGroup;

        // 加速时先移动一格
        if (poseHandler.IsFast())
        {
            const ActionType moveAction = poseHandler.IsReverse()
                                              ? ActionType::BACKWARD_1_STEP_ACTION
                                              : ActionType::FORWARD_1_STEP_ACTION;
            actionGroup.PushAction(moveAction);
        }

        // 转向（倒车时左右互换）
        if (poseHandler.IsReverse())
        {
            actionGroup.PushAction(ActionType::REVERSE_TURNLEFT_ACTION);
        }
        else
        {
            actionGroup.PushAction(ActionType::TURNLEFT_ACTION);
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

        if (poseHandler.IsFast())
        {
            const ActionType moveAction = poseHandler.IsReverse()
                                              ? ActionType::BACKWARD_1_STEP_ACTION
                                              : ActionType::FORWARD_1_STEP_ACTION;
            actionGroup.PushAction(moveAction);
        }

        if (poseHandler.IsReverse())
        {
            actionGroup.PushAction(ActionType::REVERSE_TURNRIGHT_ACTION);
        }
        else
        {
            actionGroup.PushAction(ActionType::TURNRIGHT_ACTION);
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