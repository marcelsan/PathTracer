cmake_minimum_required(VERSION 2.6)
project(PathTracer CXX)

if (UNIX AND NOT APPLE)
	set(CMAKE_CXX_COMPILER g++-4.9)
endif ()

find_package(ImageMagick COMPONENTS Magick++)
include_directories(${ImageMagick_INCLUDE_DIRS})
link_directories(${ImageMagick_LIBRARIES})
include_directories(${ImageMagick_Magick++_INCLUDE_DIRS})
link_directories(${ImageMagick_Magick++_LIBRARIES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMAGICKCORE_QUANTUM_DEPTH=16")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMAGICKCORE_HDRI_ENABLE=0")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "thirdparty/glm/")

add_subdirectory(src)