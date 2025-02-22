# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.20)

# Define the project name for the library
project(GPIO)

# Set the C++ standard to use (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

set(CMAKE_C_COMPILER "/usr/bin/aarch64-poky-linux-gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/aarch64-poky-linux-g++")
set(CMAKE_ASM_COMPILER "/usr/bin/aarch64-poky-linux-as")

# Add the include directory for the GPIO library
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Create the GPIO library
add_library(${PROJECT_NAME} STATIC ${CMAKE_SOURCE_DIR}/src/GPIO.cc)

# Link necessary libraries for the GPIO library
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)