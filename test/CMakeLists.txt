cmake_minimum_required(VERSION 3.7...3.24)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(MyProject VERSION 1.0
                  DESCRIPTION "53E test"
                  LANGUAGES CXX)
include_directories(../include/)
add_executable(main src/main.cpp)
