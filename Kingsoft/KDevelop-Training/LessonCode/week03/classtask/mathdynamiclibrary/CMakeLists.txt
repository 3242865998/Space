cmake_minimum_required(VERSION 3.10)

project(MathDynamicLibrary)

add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME} PRIVATE
    mathdynamiclibrary.h
    mathdynamiclibrary.cpp
)

target_compile_definitions(${PROJECT_NAME} PRIVATE MATHLIBRARY_EXPORTS)

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "mathdynamiclib"
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin  #.lib .exp的输出路径
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) #.dll的输出路径