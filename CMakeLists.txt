cmake_minimum_required(VERSION 3.13)
project(temp C)

set(CMAKE_C_STANDARD 11)

add_executable(main src/main.c src/vec.h)

set(CMAKE_C_FLAGS "-O3")

find_package(OpenMP)
if(OpenMP_C_FOUND)
    target_link_libraries(main PUBLIC OpenMP::OpenMP_C)
endif()

# For Debugging
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -g -O0")