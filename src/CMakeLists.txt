set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(pathtracer_SRCS
    box.cpp
    camera.cpp
    filesystemutil.cpp
	imagebuffer.cpp
	object.cpp
    quadric.cpp
    mesh.cpp
	scene.cpp
	material.cpp
	main.cpp
)

add_executable(pathtracer ${pathtracer_SRCS})
