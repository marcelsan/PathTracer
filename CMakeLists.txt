cmake_minimum_required(VERSION 2.6)
project(PathTracer CXX)

# if (UNIX)
# 	set(CMAKE_CXX_COMPILER g++-4.9)
# endif (UNIX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "thirdparty/glm/")

add_subdirectory(src)