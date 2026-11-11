#pragma once

#include <functional>
#include <list>
#include <unordered_map>
#include <string>
#include "Command.hpp"
#include "PoseHandler.hpp"

namespace adas
{

using Cmder = std::function<ActionGroup(PoseHandler&)>;
using CmderList = std::list<Cmder>;

class CmderFactory final
{
public:
    CmderFactory() = default;
    ~CmderFactory() = default;

    CmderFactory(const CmderFactory&) = delete;
    CmderFactory& operator=(const CmderFactory&) = delete;

    CmderList GetCmders(const std::string& commands) const noexcept;

private:
    std::string ParseCommandString(const std::string& commands) const noexcept;
    void ReplaceAll(std::string& inout, const std::string& what, const std::string& with) const noexcept;
    const std::unordered_map<char, Cmder> cmderMap{
    {'M', MoveCommand{}},
    {'L', TurnLeftCommand{}},
    {'R', TurnRightCommand{}},
    {'F', FastCommand{}},
    {'B', ReverseCommand{}},
    {'Z', TurnRoundCommand{}}   // TR 映射为 Z
    };
};

} // namespace adas