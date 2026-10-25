set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

ADD_SUBDIRECTORY(googletest EXCLUDE_FROM_ALL)

# 显式列出所有测试源文件（不要再用 AUX_SOURCE_DIRECTORY）
ADD_EXECUTABLE(training_main
    ExecutorTest.cpp
    ExecutorFastTest.cpp
    PoseEq.cpp
)

TARGET_LINK_LIBRARIES(training_main training gtest_main)

ADD_TEST(NAME training_main COMMAND training_main)