cmake_minimum_required(VERSION 3.16)
project(Practica4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

add_executable(practica4 src/main.cpp)
target_link_libraries(practica4 PRIVATE Threads::Threads)
