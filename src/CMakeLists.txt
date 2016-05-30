set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(pathtracer_SRCS
    object.cpp
    quadric.cpp
    box.cpp
    camera.cpp
    intersection.cpp
    mesh.cpp
    npywriter.cpp
    scene.cpp
    material.cpp
    sdlreader.cpp
    ray.cpp
    raytrace.cpp
    light.cpp
    main.cpp
    util.cpp
)

add_executable(pathtracer ${pathtracer_SRCS})

target_link_libraries(pathtracer ${ImageMagick_LIBRARIES})