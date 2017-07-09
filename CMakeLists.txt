cmake_minimum_required(VERSION 3.8)
project(Grayzer)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
message("Supported features = ${CMAKE_CXX_COMPILE_FEATURES}")

add_subdirectory(src)
#add_subdirectory(examples)
