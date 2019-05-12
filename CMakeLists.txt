cmake_minimum_required(VERSION 3.14)
project(c_vec)

set(CMAKE_CXX_STANDARD 17)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
add_subdirectory(tests) # Defines testDriver
#include_directories(src) # Has the header files used
# Normally instead of using include_directories(src) we would use a
# add_subdirectory(src), where src would have another CMakeLists.txt
# that worked similarly to the one found in tests, except we would have
# a call to add_library() instead of add_executable(). However, we don't
# do this because we don't technically have a library -- all of the function
# definitions are generated at compile-time by the C-preprocessor. To be a
# library, there must be at least on C file. So because all we have to offer
# is a handful of header files, we use only those.
add_subdirectory(src)

set(CMAKE_C_FLAGS "-O3 -Wall -pedantic -std=c11")
set(CMAKE_CXX_FLAGS "-O3 -Wall -pedantic -std=c++17")

# Set the flags to handle OpenMP
#set(CLANG_FLAGS "-Ofast -Weverything -Wpedantic -std=c11 -fopenmp -lomp")
#set(APPLE_CLANG_FLAGS "-Xpreprocessor")
#set(BREW_CLANG_FLAGS "-L/usr/local/opt/llvm/lib -Wl,-rpath,/usr/local/opt/llvm/lib -I/usr/local/opt/llvm/include")
#set(GCC_FLAGS "-O3 -Wall -pedantic -std=c11 -fopenmp")
#
#if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
#    set(CMAKE_C_FLAGS "${APPLE_CLANG_FLAGS} ${CLANG_FLAGS}")
#elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
#    if(APPLE)
#        set(CMAKE_C_FLAGS "${BREW_CLANG_FLAGS} ${CLANG_FLAGS}")
#    else()
#        set(CMAKE_C_FLAGS "${CLANG_FLAGS}")
#    endif(APPLE)
#elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
#    set(CMAKE_C_FLAGS "${GCC_FLAGS}")
#endif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
#
#
#find_package(OpenMP)
#if(OpenMP_C_FOUND)
#    target_link_libraries(testDriver PUBLIC OpenMP::OpenMP_C c_vec_lib gtest_main)
#else()
    target_link_libraries(testDriver c_vec_lib gtest_main)
#endif()

# For Debugging
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -g -O0")



