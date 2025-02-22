# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.20)

# Define the project name for the library
project(LED)

# Set the C++ standard to use (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

set(CMAKE_C_COMPILER "/usr/bin/aarch64-poky-linux-gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/aarch64-poky-linux-g++")
set(CMAKE_ASM_COMPILER "/usr/bin/aarch64-poky-linux-as")

# Create the LED library
add_library(${PROJECT_NAME} STATIC ${CMAKE_SOURCE_DIR}/src/LED.cc)

# Link GPIO
target_link_libraries(${PROJECT_NAME} PUBLIC GPIO)

# Set the include directories
target_include_directories(${PROJECT_NAME} PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
    "${CMAKE_CURRENT_SOURCE_DIR}/../GPIO/inc"
)