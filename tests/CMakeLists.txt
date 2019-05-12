cmake_minimum_required(VERSION 3.14)
project(testDriver)

set(CMAKE_CXX_STANDARD 17)

add_executable(testDriver testDriver.cpp andOrTest.cpp concatTest.cpp)