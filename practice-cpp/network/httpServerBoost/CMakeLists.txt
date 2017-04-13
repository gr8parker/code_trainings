cmake_minimum_required(VERSION 2.8) # check cmake version

project(myserver)

#set(boost_INCLUDE_DIR /home/box/boost)
#set(boost_LD_PATH /home/box/boost/stage/lib)

include (boost.cmake)
include_directories( ${boost_INCLUDE_DIR} )

add_compile_options(-std=c++11)

LINK_DIRECTORIES(${boost_LD_PATH})

set(CMAKE_EXE_LINKER_FLAGS "-pthread -lboost_system -lboost_thread")

add_library(session SHARED lib/session.cpp )
add_library(server SHARED lib/server.cpp )

add_executable(httpserver main.cpp)

target_link_libraries(httpserver server session  ${CMAKE_EXE_LINKER_FLAGS})
message("boost ld path: ${boost_LD_PATH}")
message("boost installed path: ${boost_INSTALL}")
