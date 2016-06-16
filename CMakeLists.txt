cmake_minimum_required(VERSION 2.6)
project(PathTracer CXX)

if (UNIX AND NOT APPLE)
	# set(CMAKE_CXX_COMPILER g++-4.9)
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "thirdparty/glm/")

add_subdirectory(src)
