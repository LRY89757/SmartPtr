cmake_minimum_required(VERSION 3.8)
set(projectname smartptr)
PROJECT(${projectname} LANGUAGES CXX) 

# 指定为C++11 版本
set(CMAKE_CXX_STANDARD 11)

add_executable(test test.cpp)