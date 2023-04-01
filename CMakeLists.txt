cmake_minimum_required(VERSION 3.6)
project(53E)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_coverage tests coverage)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -Wall -Wextra -Wshadow -Wnull-dereference -Wno-psabi -Wno-unused-function -pthread -g -O0 -fprofile-arcs -ftest-coverage -D THREADS_STD")

enable_testing()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in external-dependencies/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/external-dependencies )
if(result)
    message(FATAL_ERROR "CMake step for dependencies failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/external-dependencies )
if(result)
    message(FATAL_ERROR "Build step for dependencies failed: ${result}")
endif()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
    include_directories("${squiggles_SOURCE_DIR}/include")
endif()


include_directories(include)
add_executable(53E
  include/utils.hpp
  include/subsystems/chassis/chassis.hpp
  include/subsystems/chassis/odometry.hpp
  include/subsystems/point.hpp
  include/subsystems/pid.hpp
  #src/subsystems/chassis/chassis.cpp
  #src/subsystems/chassis/odometry.cpp
  src/subsystems/point.cpp
  src/utils/misc.cpp
  test/main.cpp
  )


# Link against gtest
target_link_libraries(53E gtest)
