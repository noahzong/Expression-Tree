cmake_minimum_required(VERSION 3.18)
project(ExpressionTree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Add in all of the header files
include_directories("./include")

# Bring together the sub-libraries
add_library(Core STATIC)
add_subdirectory(./src/commands)
add_subdirectory(./src/core)
add_subdirectory(./src/interpreter)
add_subdirectory(./src/tree)
add_subdirectory(./src/visitors)

# Generate binaries in the bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Build GTest automated testing suite
add_executable(testing)
add_subdirectory(./tests)
add_dependencies(testing gtest Core)
target_link_libraries(testing gtest ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(testing Core)

# Build interactive ExpressionTree application
add_executable(ExpressionTree ./src/main.cpp)
add_dependencies(ExpressionTree Core)
target_link_libraries(ExpressionTree Core)
