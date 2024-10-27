cmake_minimum_required(VERSION 3.10)
project(MarioGame)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the raylib library and include directories
set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/lib")
set(RAYLIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(RAYLIB_LIBRARY "${RAYLIB_DIR}/libraylib.a")

# Include directories for raylib and your headers
include_directories(${RAYLIB_INCLUDE_DIR} src)

# Find all .cpp files in src directory
file(GLOB_RECURSE SOURCES src/*.cpp)

# Define the executable
add_executable(MarioGame ${SOURCES})

# Link raylib and necessary libraries depending on the platform
if (WIN32)
    # For Windows, link with raylib and WinMM library
    target_link_libraries(MarioGame PRIVATE ${RAYLIB_LIBRARY} -lwinmm)
elseif (UNIX)
    # For Linux, link with raylib and additional dependencies
    target_link_libraries(MarioGame PRIVATE
        ${RAYLIB_LIBRARY}
        -lGL -lm -lpthread -ldl -lrt -lX11
    )
endif()

# Compiler flags (optional)
target_compile_options(MarioGame PRIVATE -Wall -Wextra -pedantic)
