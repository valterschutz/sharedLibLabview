project(sharedLibLabview LANGUAGES C CXX)
cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--disable-new-dtags")

# Set the RPATH to the install directory
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib/")
# Tell linker to set RPATH to the install directory, outside the build tree
# Note: this has to be done before add_executable/add_library.
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

include(GNUInstallDirs)
find_package(Boost REQUIRED)

# addTwo, no dependency on libraries
add_library(addTwo SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/src/addTwo.cpp
)
target_include_directories(addTwo PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)
set_property(TARGET addTwo PROPERTY
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/inc/addTwo.hpp
)

# tcpServer, depends on Boost::asio. Since asio is header only, no need
# to link it?
add_library(tcpServer SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tcpServer.cpp
)
target_include_directories(tcpServer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${Boost_INCLUDE_DIRS}
)
set_property(TARGET tcpServer PROPERTY
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/inc/tcpServer.hpp
)
