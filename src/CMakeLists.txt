set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(pathtracer_SRCS
    object.cpp
    quadric.cpp
    box.cpp
    camera.cpp
	imagebuffer.cpp
    mesh.cpp
	scene.cpp
	material.cpp
    filesystemutil.cpp
    ray.cpp
    raytrace.cpp
	main.cpp
)

add_executable(pathtracer ${pathtracer_SRCS})
