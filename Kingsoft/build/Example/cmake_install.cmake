# Install script for directory: D:/KingSoft/developmentPath/KDevelop-Training/Example

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Develop-Train")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/KingSoft/developmentPath/build/Example/QtDemo/cmake_install.cmake")
  include("D:/KingSoft/developmentPath/build/Example/CppBase/cmake_install.cmake")
  include("D:/KingSoft/developmentPath/build/Example/GMockExample/cmake_install.cmake")
  include("D:/KingSoft/developmentPath/build/Example/GtestExample/cmake_install.cmake")
  include("D:/KingSoft/developmentPath/build/Example/PersonCpp/cmake_install.cmake")
  include("D:/KingSoft/developmentPath/build/Example/PersonMain/cmake_install.cmake")
  include("D:/KingSoft/developmentPath/build/Example/QtChart/cmake_install.cmake")

endif()

