cmake_minimum_required(VERSION 3.10)

project(KMemoryPool)

# 添加执行文件
add_executable(${PROJECT_NAME} 
    main.cpp
)

target_sources(${PROJECT_NAME} PRIVATE
	kmemorypool.h
	kmemorypool.cpp
	kmemorypoolmanager.h
	kmemorypoolmanager.cpp
	main.cpp
)

if(WIN32)
    target_link_options(${PROJECT_NAME} PRIVATE /SUBSYSTEM:CONSOLE)
endif()

