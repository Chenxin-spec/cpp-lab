#include <gtest/gtest.h>
#include "Executor.hpp"

TEST(ExecutorTest, should_return_init_pose_when_without_command)
{
    Pose init{1, 2, 0};
    auto exe = Executor::NewExecutor(init);
    Pose res = exe->Query();
    ASSERT_EQ(res.x, 1);
    ASSERT_EQ(res.y, 2);
    ASSERT_EQ(res.heading, 0);
}

TEST(ExecutorTest, should_return_default_pose_when_without_init_and_command)
{
    auto exe = Executor::NewExecutor();
    Pose res = exe->Query();
    ASSERT_EQ(res.x, 0);
    ASSERT_EQ(res.y, 0);
    ASSERT_EQ(res.heading, 78);
}

TEST(ExecutorTest, should_x_plus1_when_M_and_facing_E)
{
    Pose init{0, 0, 69};
    auto exe = Executor::NewExecutor(init);
    exe->Execute("M");
    Pose res = exe->Query();
    ASSERT_EQ(res.x, 1);
    ASSERT_EQ(res.y, 0);
    ASSERT_EQ(res.heading, 69);
}

TEST(ExecutorTest, should_y_plus1_when_M_and_facing_N)
{
    Pose init{0, 0, 0};
    auto exe = Executor::NewExecutor(init);
    exe->Execute("M");
    Pose res = exe->Query();
    ASSERT_EQ(res.x, 0);
    ASSERT_EQ(res.y, 1);
    ASSERT_EQ(res.heading, 0);
}

TEST(ExecutorTest, should_y_minus1_when_M_and_facing_S)
{
    Pose init{0, 0, 159};
    auto exe = Executor::NewExecutor(init);
    exe->Execute("M");
    Pose res = exe->Query();
    ASSERT_EQ(res.x, 0);
    ASSERT_EQ(res.y, -1);
    ASSERT_EQ(res.heading, 159);
}

TEST(ExecutorTest, should_x_minus1_when_M_and_facing_W)
{
    Pose init{0, 0, 249};
    auto exe = Executor::NewExecutor(init);
    exe->Execute("M");
    Pose res = exe->Query();
    ASSERT_EQ(res.x, -1);
    ASSERT_EQ(res.y, 0);
    ASSERT_EQ(res.heading, 249);
}

TEST(ExecutorTest, should_turn_right_when_facing_N)
{
    Pose init{0,0,0};
    auto exe = Executor::NewExecutor(init);
    exe->Execute("R");
    Pose res = exe->Query();
    ASSERT_EQ(res.heading, 69);
}

TEST(ExecutorTest, should_turn_right_when_facing_E)
{
    Pose init{0,0,69};
    auto exe = Executor::NewExecutor(init);
    exe->Execute("R");
    Pose res = exe->Query();
    ASSERT_EQ(res.heading, 159);
}

TEST(ExecutorTest, should_turn_right_when_facing_S)
{
    Pose init{0,0,159};
    auto exe = Executor::NewExecutor(init);
    exe->Execute("R");
    Pose res = exe->Query();
    ASSERT_EQ(res.heading, 249);
}

TEST(ExecutorTest, should_turn_right_when_facing_W)
{
    Pose init{0,0,249};
    auto exe = Executor::NewExecutor(init);
    exe->Execute("R");
    Pose res = exe->Query();
    ASSERT_EQ(res.heading, 0);
}


TEST(ExecutorTest, should_turn_left_when_facing_N)
{
    Pose init{0,0,0};
    auto exe = Executor::NewExecutor(init);
    exe->Execute("L");
    Pose res = exe->Query();
    ASSERT_EQ(res.heading, 249);
}
