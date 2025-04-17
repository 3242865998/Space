cmake_minimum_required(VERSION 3.10)

project(mathstaticlibrary)

add_library(${PROJECT_NAME} STATIC)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_sources(${PROJECT_NAME} PRIVATE
    mathstaticlibrary.h
    mathstaticlibrary.cpp
)