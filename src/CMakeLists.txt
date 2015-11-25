set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(pathtracer_SRCS
	object.cpp
	scene.cpp
	main.cpp
)

add_executable(pathtracer ${pathtracer_SRCS})
