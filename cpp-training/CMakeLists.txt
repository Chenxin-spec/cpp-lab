cmake_minimum_required(VERSION 3.15)
PROJECT(cpp-training VERSION 0.1.0)

SET(CMAKE_CXX_STANDARD 17)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    SET(CMAKE_CXX_FLAGS "-Wno-deprecated-declarations -Wall -Werror -Wnon-virtual-dtor -Woverloaded-virtual")
endif()

ENABLE_TESTING()
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tests)
