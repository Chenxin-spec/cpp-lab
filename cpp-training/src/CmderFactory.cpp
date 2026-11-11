#include "CmderFactory.hpp"
#include <string_view>

namespace adas
{

CmderList CmderFactory::GetCmders(const std::string& commands) const noexcept
{
    CmderList cmders;

    for (const auto cmd : ParseCommandString(commands))
    {
        const auto it = cmderMap.find(cmd);
        if (it != cmderMap.end())
        {
            cmders.push_back(it->second);
        }
    }

    return cmders;
}

std::string CmderFactory::ParseCommandString(const std::string& commands) const noexcept
{
    std::string result(commands);
    ReplaceAll(result, "TR", "Z");
    return result;
}

void CmderFactory::ReplaceAll(std::string& inout, const std::string& what, const std::string& with) const noexcept
{
    for (std::string::size_type pos = 0;
         (pos = inout.find(what, pos)) != std::string::npos;
         pos += with.length())
    {
        inout.replace(pos, what.length(), with);
    }
}

} // namespace adas