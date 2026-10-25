#include <gtest/gtest.h>
#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{

// F + M ：加速状态下前进两格
TEST(ExecutorFastTest, should_return_x_plus_2_given_status_is_fast_command_is_M_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 69})); // E
    // when
    executor->Execute("FM");
    // then
    const Pose target{2, 0, 69};
    ASSERT_EQ(target, executor->Query());
}

// F + L ：加速状态下先前进一格再左转
TEST(ExecutorFastTest, should_return_N_and_x_plus_1_given_status_is_fast_command_is_L_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 69})); // E
    // when
    executor->Execute("FL");
    // then
    const Pose target{1, 0, 0}; // N
    ASSERT_EQ(target, executor->Query());
}

// F + R ：加速状态下先前进一格再右转
TEST(ExecutorFastTest, should_return_S_and_x_plus_1_given_status_is_fast_given_command_is_R_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 69})); // E
    // when
    executor->Execute("FR");
    // then
    const Pose target{1, 0, 159}; // S
    ASSERT_EQ(target, executor->Query());
}

// FF + M ：第二次 F 取消加速，只前进一格
TEST(ExecutorFastTest, should_return_y_plus_1_given_command_is_FFM_and_facing_is_N)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 0})); // N
    // when
    executor->Execute("FFM");
    // then
    const Pose target{0, 1, 0};
    ASSERT_EQ(target, executor->Query());
}

} // namespace adas