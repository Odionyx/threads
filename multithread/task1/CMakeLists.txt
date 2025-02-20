cmake_minimum_required(VERSION 3.20)

project(task1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(task1 main.cpp)

install(TARGETS task1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
