cmake_minimum_required(VERSION 3.0)
project(arrays_proj)

set(SOURCE_EXE main.c)
set(SOURCE_LIB array.c)

add_library(array STATIC ${SOURCE_LIB})
add_executable(main ${SOURCE_EXE})
target_link_libraries(main array)