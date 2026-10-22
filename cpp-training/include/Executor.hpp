#pragma once
#include <memory>
#include <string>
#include <cmath>
#include <ostream>

struct Pose {
    double x;
    double y;
    double heading;
};

inline bool operator==(const Pose& a, const Pose& b)
{
    const double eps = 1e-9;
    return std::fabs(a.x - b.x) < eps
        && std::fabs(a.y - b.y) < eps
        && std::fabs(a.heading - b.heading) < eps;
}

inline std::ostream& operator<<(std::ostream& os, const Pose& p)
{
    os << "Pose(x=" << p.x << ", y=" << p.y << ", heading=" << p.heading << ")";
    return os;
}

class Executor {
public:
    virtual ~Executor() = default;
    virtual void Execute(const std::string& command) noexcept = 0;
    virtual Pose Query() const noexcept = 0;

    static std::unique_ptr<Executor> NewExecutor(const Pose& init_pose);
    static std::unique_ptr<Executor> NewExecutor();
};
