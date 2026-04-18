cmake_minimum_required(VERSION 3.28)
project(SortingSrc)
set(CMAKE_CXX_STANDARD 20)

set(SRC_LIB_NAME SortingSrc)
set(EXE_NAME SortInts)


add_library(${SRC_LIB_NAME} STATIC sorting.c sorting.h formatting.c formatting.h)
target_include_directories(${SRC_LIB_NAME}  PUBLIC .)
target_compile_options(${SRC_LIB_NAME}  PRIVATE ${CXX_WARNINGS})

add_executable(${EXE_NAME} main.c)
target_link_libraries(${EXE_NAME} PRIVATE ${SRC_LIB_NAME})
target_compile_options(${EXE_NAME} PRIVATE ${CXX_WARNINGS})
