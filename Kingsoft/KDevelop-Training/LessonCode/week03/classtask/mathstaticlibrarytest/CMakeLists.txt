cmake_minimum_required(VERSION 3.10) 

project(mathstaticlibrarytest) 

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/../mathstaticlibrary
)

target_link_libraries(${PROJECT_NAME} PRIVATE
mathstaticlibrary)