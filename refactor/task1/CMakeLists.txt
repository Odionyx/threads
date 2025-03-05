cmake_minimum_required(VERSION 3.20)

project(task1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SOURCES
    main.cpp
    shape.cpp
)
set (HEADERS
    shape.h
)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
