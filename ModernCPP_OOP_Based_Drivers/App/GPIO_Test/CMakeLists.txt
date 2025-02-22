# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.20)

# Define the project name for the test
project(GPIO_Test)

# Set the C++ standard to use (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

set(CMAKE_C_COMPILER "/usr/bin/aarch64-poky-linux-gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/aarch64-poky-linux-g++")
set(CMAKE_ASM_COMPILER "/usr/bin/aarch64-poky-linux-as")

# Add the include directory for the GPIO library
include_directories(${CMAKE_SOURCE_DIR}/../../GPIO/inc)

# Specify the path to the precompiled GPIO library
set(LIBRARY_PATH ${CMAKE_SOURCE_DIR}/../../GPIO/build)

# Create the example executable
add_executable(${PROJECT_NAME} main.cc)

# Link the GPIO library to the example executable
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARY_PATH}/libGPIO.a)

# Set permissions for /dev/mem (optional, for convenience during development)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND chmod u+s $<TARGET_FILE:${PROJECT_NAME}>
        COMMENT "Setting setuid bit for accessing /dev/mem"
    )
endif()