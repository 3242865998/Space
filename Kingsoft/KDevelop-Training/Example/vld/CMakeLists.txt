cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(vld)

# 检查编译架构
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH_DIR "Win64")
else()
    set(ARCH_DIR "Win32")
endif()

# 获取对应架构目录下的所有文件
file(GLOB LIB_FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCH_DIR}/*)

# 复制文件到 test 目录
foreach(FILE ${LIB_FILES})
    get_filename_component(FILE_NAME ${FILE} NAME)
    configure_file(${FILE} ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/${FILE_NAME} COPYONLY)
endforeach()    