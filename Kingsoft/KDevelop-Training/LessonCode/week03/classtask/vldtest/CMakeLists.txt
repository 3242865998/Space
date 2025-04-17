cmake_minimum_required(VERSION 3.10)  #cmake版本最低3.10

project(vldtest)  #添加当前项目名称

add_executable(${PROJECT_NAME}
	main.cpp)

#向工程添加源码
target_sources(${PROJECT_NAME} PRIVATE
    main.cpp
)

#向工程添加多个特定头文件的搜索路径——   -I参数
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../vld/include
)

if(CMAKE_GENERATOR_PLATFORM STREQUAL "x64")
    set(LIB_DIR_SUFFIX "Win64")
elseif(CMAKE_GENERATOR_PLATFORM STREQUAL "Win32")
    set(LIB_DIR_SUFFIX "Win32")
endif()

set(VLD_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../vld/lib/${LIB_DIR_SUFFIX}/vld.lib)

#链接VLD的库文件
target_link_libraries(${PROJECT_NAME} PRIVATE ${VLD_LIB_PATH})