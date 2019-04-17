cmake_minimum_required(VERSION 3.13)
project(vec_c C)

set(CMAKE_C_STANDARD 11)

add_executable(main src/main.c src/vec.h)
add_executable(and_or_example src/and_or_example.c)
add_executable(concat_example src/concat_example.c)
add_executable(foldl_foldr_example src/foldl_foldr_example.c)

set(CLANG_FLAGS "-Ofast -Weverything -Wpedantic -std=c11 -fopenmp -lomp")
set(APPLE_CLANG_FLAGS "-Xpreprocessor")
set(BREW_CLANG_FLAGS "-L/usr/local/opt/llvm/lib -Wl,-rpath,/usr/local/opt/llvm/lib -I/usr/local/opt/llvm/include")
set(GCC_FLAGS "-O3 -Wall -pedantic -std=c11 -fopenmp")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    set(CMAKE_C_FLAGS "${APPLE_CLANG_FLAGS} ${CLANG_FLAGS}")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    if(APPLE)
        set(CMAKE_C_FLAGS "${BREW_CLANG_FLAGS} ${CLANG_FLAGS}")
    else()
        set(CMAKE_C_FLAGS "${CLANG_FLAGS}")
    endif(APPLE)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_C_FLAGS "${GCC_FLAGS}")
endif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")


find_package(OpenMP)
if(OpenMP_C_FOUND)
    target_link_libraries(main PUBLIC OpenMP::OpenMP_C)
endif()

# For Debugging
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -g -O0")