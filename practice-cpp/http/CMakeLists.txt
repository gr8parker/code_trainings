cmake_minimum_required(VERSION 2.8) # check cmake version

add_compile_options(-std=c++11)

project(httpserver)

include_directories(lib)

find_package(Boost COMPONENTS system thread REQUIRED)
if(!Boost_SYSTEM_FOUND)
	message(SEND_ERROR "boost_system was not found")
	return()
endif()	

if(!Boost_THREAD_FOUND)
	message(SEND_ERROR "boost_thred was not found")
endif()

set(CMAKE_EXE_LINKER_FLAGS "-lboost_system -lboost_thread -pthread")

add_library(session SHARED lib/session.cpp )
add_library(server SHARED lib/server.cpp )

add_executable(final main.cpp)

target_link_libraries(final session server ${CMAKE_EXE_LINKER_FLAGS} )
