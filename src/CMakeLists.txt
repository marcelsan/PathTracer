set(CMAKE_C_FLAGS "-Wall -g" )

file(GLOB SRCS *.cpp *.h)

add_executable(pathtracer ${SRCS})
