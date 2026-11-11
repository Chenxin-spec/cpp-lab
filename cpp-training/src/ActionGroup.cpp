#include "ActionGroup.hpp"

#include <algorithm>
#include <functional>  // 必须加这个
#include <vector>

namespace adas
{

// 原子操作实现
class ForwardAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Forward();
    }
};

class BackwardAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Backward();
    }
};

class TurnLeftAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.TurnLeftImpl();   // 改成 Impl
    }
};

class ReverseTurnLeftAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.TurnRightImpl();   // BL 时需要右转
    }
};

class TurnRightAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.TurnRightImpl();  
    }
};

class ReverseTurnRightAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.TurnLeftImpl();    // BR 时需要左转
    }
};

class BeFastAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Fast();
    }
};

class BeReverseAction final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Reverse();
    }
};

// ActionGroup 实现
ActionGroup::ActionGroup(const std::list<ActionType>& actions) noexcept : actions(actions)
{
}

void ActionGroup::PushAction(const ActionType actionType) noexcept
{
    actions.push_back(actionType);
}

void ActionGroup::DoOperate(PoseHandler& poseHandler) const noexcept
{
    static const std::vector<std::function<void(PoseHandler&)>> actionVec = {
        ForwardAction{},   BackwardAction{},         TurnLeftAction{}, ReverseTurnLeftAction{},
        TurnRightAction{}, ReverseTurnRightAction{}, BeFastAction{},   BeReverseAction{},
    };

    std::for_each(actions.begin(), actions.end(), [&poseHandler](const ActionType actionType) noexcept {
        actionVec[static_cast<uint16_t>(actionType)](poseHandler);
    });
}

ActionGroup::ActionGroup(std::initializer_list<ActionType> actions) noexcept
    : actions(actions)
{
}

}  // namespace adas