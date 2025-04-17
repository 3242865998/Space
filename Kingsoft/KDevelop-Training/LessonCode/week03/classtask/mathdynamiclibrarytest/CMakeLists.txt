cmake_minimum_required(VERSION 3.10)

project(MathDynamicLibraryTest)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}/../MathDynamicLibrary
)

target_link_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_BINARY_DIR}/bin
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    mathdynamiclib
)